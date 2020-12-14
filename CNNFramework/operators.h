#include <math.h>

struct conv {
    int shape[4]; // out channel, in channel, size
    double *weight;
    double *bias;
    int padding;
    int stride;
};

struct fc {
    int shape[2]; // out channel, in channel
    double *weight;
    double *bias;
};

struct activation {
    int shape[3]; // channel, size
    double *val;
};

void print_act(struct activation *act) {
    int i, j, k;
    for (i = 0; i < act->shape[0]; ++i) {
        for (j = 0; j < act->shape[1]; ++j) {
            for (k = 0; k < act->shape[2]; ++k)
                printf("%lf ", act->val[i * act->shape[1] * act->shape[2] + j * act->shape[2] + k]);
            printf("\n");
        }
        printf("\n");
    }
}

void print_layer(struct conv *layer) {
    int i, j, k, l;
    for (i = 0; i < layer->shape[0]; ++i) {
        for (j = 0; j < layer->shape[1]; ++j) {
            for (k = 0; k < layer->shape[2]; ++k) {
                for (l = 0; l < layer->shape[3]; ++l)
                    printf("%lf ", layer->weight[i * layer->shape[1] * layer->shape[2] * layer->shape[3] + j * layer->shape[2] * layer->shape[3] + k * layer->shape[3] + l]);
                printf("\n");
            }
            printf("\n");
        }
        printf("\n");
    }
}

double maxi(double x, double y) {
    return x > y ? x : y;
}

int Classification(struct activation *act) {
    int i, maxind = -1;
    double m = -1;
    for (i = 0; i < act->shape[0] * act->shape[1] * act->shape[2]; ++i) {
        //printf("%lf\n", act->val[i]);
        if (m < act->val[i]) {
            m = act->val[i];
            maxind = i;
        }
    }
    return maxind;
}

void ReLU(struct activation *act) {
    int i, j, k;
    for (i = 0; i < act->shape[0]; ++i)
        for (j = 0; j < act->shape[1]; ++j)
            for (k = 0; k < act->shape[2]; ++k)
                if (act->val[i * act->shape[1] * act->shape[2] + j * act->shape[2] + k] < 0)
                    act->val[i * act->shape[1] * act->shape[2] + j * act->shape[2] + k] = 0;
    return;
}

struct activation *MaxPooling(struct activation *act, int x, int y) {
    struct activation *out = malloc(sizeof(struct activation));
    int i, j, k, a, b, nx = ceil((double)act->shape[1] / x), ny = ceil((double)act->shape[2] / y);
    out->shape[0] = act->shape[0];
    out->shape[1] = nx; out->shape[2] = ny;
    out->val = (double *)malloc(sizeof(double) * out->shape[0] * out->shape[1] * out->shape[2]);
    for (i = 0; i < act->shape[0]; ++i)
        for (j = 0; j < nx; ++j)
            for (k = 0; k < ny; ++k) {
                out->val[i * nx * ny + j * ny + k] = act->val[i * nx * ny * x * y + j * x * ny * y + k * y];
                for (a = 0; a < x; ++a) {
                    if (j * x + a>= act->shape[1]) break;
                    for (b = 0; b < y; ++b) {
                        if (k * y + b >= act->shape[2]) break;
                        out->val[i * nx * ny + j * ny + k] = maxi(out->val[i * nx * ny + j * ny + k], act->val[i * nx * ny * x * y + (j * x + a) * ny * y + k * y + b]);
                    }
                }
            }
    free(act->val);
    free(act);
    return out;
} 

struct activation *Pad(struct activation *act, int padding) {
    struct activation *newact = malloc(sizeof(struct activation));
    newact->shape[0] = act->shape[0];
    newact->shape[1] = act->shape[1] + 2 * padding;
    newact->shape[2] = act->shape[2] + 2 * padding;
    newact->val = (double *)malloc(sizeof(double) * newact->shape[0] * newact->shape[1] * newact->shape[2]);
    int i, j, k;
    for (i = 0; i < newact->shape[0]; ++i)
        for (j = 0; j < newact->shape[1]; ++j)
            for (k = 0; k < newact->shape[2]; ++k)
                if (j < padding || k < padding || j >= newact->shape[1] - padding || k >= newact->shape[2] - padding) 
                    newact->val[i * newact->shape[1] * newact->shape[2] + j * newact->shape[2] + k] = 0;
                else 
                    newact->val[i * newact->shape[1] * newact->shape[2] + j * newact->shape[2] + k] = \
                        act->val[i * act->shape[1] * act->shape[2] + (j - padding) * act->shape[2] + k - padding];
    free(act->val);
    free(act);
    act = newact;
    return act;
}

struct activation *Convolution(struct activation *act, struct conv *layer) {
    if (layer->padding > 0)
        act = Pad(act, layer->padding);

    struct activation *out = malloc(sizeof(struct activation));
    out->shape[0] = layer->shape[0];
    out->shape[1] = (act->shape[1] - layer->shape[2]) / layer->stride + 1;
    out->shape[2] = (act->shape[2] - layer->shape[3]) / layer->stride + 1;
    out->val = (double *)malloc(sizeof(double) * out->shape[0] * out->shape[1] * out->shape[2]);
    int i, j, k;
    int a, b, c;
    for (i = 0; i < out->shape[0]; ++i) 
        for (j = 0; j < out->shape[1]; ++j)
            for (k = 0; k < out->shape[2]; ++k) {
                out->val[i * out->shape[1] * out->shape[2] + j * out->shape[2] + k] = layer->bias[i];
                for (a = 0; a < layer->shape[1]; ++a)
                    for (b = 0; b < layer->shape[2]; ++b)
                        for (c = 0; c < layer->shape[3]; ++c) {
                            out->val[i * out->shape[1] * out->shape[2] + j * out->shape[2] + k] += \
                                layer->weight[i * layer->shape[1] * layer->shape[2] * layer->shape[3] + a * layer->shape[2] * layer->shape[3] + b * layer->shape[3] + c]*\
                                    act->val[a * act->shape[1] * act->shape[2] + (layer->stride * j + b) * act->shape[2] + (layer->stride * k + c)];
                        }
            }
    free(act->val);
    free(act);
    return out;
}

struct activation *FullConection(struct activation *act, struct fc *layer) {
    int i, j;
    struct activation *out = malloc(sizeof(struct activation));
    out->val = (double *)malloc(sizeof(double) * layer->shape[0]);
    out->shape[0] = layer->shape[0];
    out->shape[1] = out->shape[2] = 1;
    
    for (i = 0; i < layer->shape[0]; ++i) {
        out->val[i] = layer->bias[i];
        for (j = 0; j < layer->shape[1]; ++j)
            out->val[i] += act->val[j] * layer->weight[i * layer->shape[1] + j];       
    }
    free(act->val);
    free(act);
    return out;
}
