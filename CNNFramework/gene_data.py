import torch
import torchvision
import torch.utils.data as data

test_data = torchvision.datasets.MNIST(
    root = './mnist',
    train = False,
    transform = torchvision.transforms.ToTensor(),
    download = True
)

test_loader = data.DataLoader(
    dataset = test_data,
    batch_size = 1,
    num_workers = 2
)

with open('cdata.dat', 'w') as f:
    for (x, y) in test_loader:
        f.write(str(x.shape[2]) + ' ' + str(x.shape[3]) + '\n')
        for a in x:
            for b in a:
                for c in b:
                    for d in c:
                        f.write(str(float(d)) + ' ')
                    f.write('\n')
        f.write(str(int(y)) + '\n')
