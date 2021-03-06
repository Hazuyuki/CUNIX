#include "operators.h"
#include <stdio.h>
#include <string.h>

struct activation *inference(struct activation *input) {
    struct activation *act = input;
    FILE *f = fopen("cnn.cm", "r");
    char str[128];
    while (1) {
        fgets(str, 128, f);
        if (strcmp(str, "Conv\n\0") == 0) {
            struct conv *layer = malloc(sizeof(struct conv));
            fscanf(f, "%d%d", &layer->padding, &layer->stride);
            fscanf(f, "%d%d%d%d", &layer->shape[0], &layer->shape[1], &layer->shape[2], &layer->shape[3]);
 
            int i, j, k, l;
            layer->weight = (double *)malloc(sizeof(double) * layer->shape[0] * layer->shape[1] * layer->shape[2] * layer->shape[3]);
            for (i = 0; i < layer->shape[0]; ++i) 
                for (j = 0; j < layer->shape[1]; ++j)
                    for (k = 0; k < layer->shape[2]; ++k)
                        for (l = 0; l < layer->shape[3]; ++l)
                            fscanf(f, "%lf", &layer->weight[i * layer->shape[1] * layer->shape[2] * layer->shape[3] + j * layer->shape[2] * layer->shape[3] + k * layer->shape[3] + l]);

            fscanf(f, "%d", &layer->shape[0]);
            layer->bias = (double *)malloc(sizeof(double) * layer->shape[0]); 
            for (i = 0; i < layer->shape[0]; ++i)
                fscanf(f, "%lf", &layer->bias[i]);

            act = Convolution(act, layer);
            free(layer->weight);
            free(layer->bias);
            free(layer);
        }
        if (strcmp(str, "ReLU\n\0") == 0) {
            ReLU(act);
        }
        if (strcmp(str, "MaxP\n\0") == 0) { 
            int x, y;
            fscanf(f, "%d%d", &x, &y); 
            act = MaxPooling(act, x, y);
        }
        if (strcmp(str, "FC\n\0") == 0) {
            struct fc *layer = malloc(sizeof(struct fc));
            fscanf(f, "%d%d", &layer->shape[0], &layer->shape[1]);
            int i, j;
            layer->weight = (double *)malloc(sizeof(double) * layer->shape[0] * layer->shape[1]);
            for (i = 0; i < layer->shape[0]; ++i)
                for (j = 0; j < layer->shape[1]; ++j)
                    fscanf(f, "%lf", &layer->weight[i * layer->shape[1] + j]);
            
            fscanf(f, "%d", &layer->shape[0]);
            layer->bias = (double *)malloc(sizeof(double) * layer->shape[0]);
            for (i = 0; i < layer->shape[0]; ++i)
                fscanf(f, "%lf", &layer->bias[i]);
            act = FullConection(act, layer);
            free(layer->weight);
            free(layer->bias);
            free(layer);
        }
        if (strcmp(str, "OUTPUT\n\0") == 0) {
            return act;
        }
        if (strcmp(str, "\n\0") == 0) {
            continue;
        }
    }
}

struct activation *dataloader(FILE *f) {
    struct activation *input = malloc(sizeof(struct activation));
    input->shape[0] = 1;
    fscanf(f, "%d%d", &input->shape[1], &input->shape[2]);
    input->val = (double *)malloc(sizeof(double) * input->shape[0] * input->shape[1] * input->shape[2]);
    int i, j;

    for (j = 0; j < input->shape[2] + 2; ++j) printf("==");
    printf("\n");
    for (i = 0; i < input->shape[1]; ++i) {
        printf("||");
        for (j = 0; j < input->shape[2]; ++j) {
            fscanf(f, "%lf", &input->val[i * input->shape[2] + j]);
            if (input->val[i * input->shape[2] + j] > 0.67) printf("@@");
            else if ((input->val[i * input->shape[2] + j] > 0.33)) printf("oo");
            else printf("  ");
        }
        printf("||\n");
    }
    for (j = 0; j < input->shape[2] + 2; ++j) printf("=="); 
    printf("\n");

    int label;
    fscanf(f, "%d", &label);
    printf("true label is: %d\n", label);
    return input;
}

int main()
{
    FILE *f = fopen("cdata.dat", "r");
    while (1) {
        struct activation *input = dataloader(f);
        struct activation *output = inference(input);
        int ans = Classification(output);
        printf("inference result is: %d\nPress ENTER to continue:", ans); 
        getchar(); 
    }
}