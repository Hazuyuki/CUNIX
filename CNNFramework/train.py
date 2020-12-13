import torch
import torch.nn as nn
import torch.nn.functional as func
import torchvision
import torch.utils.data as data

BATCH_SIZE = 128;

train_data = torchvision.datasets.MNIST(
    root = './mnist',
    train = True,
    transform = torchvision.transforms.ToTensor(),
    download = False
)

train_loader = data.DataLoader(
    dataset = train_data,
    batch_size = BATCH_SIZE,
    shuffle = True,
    num_workers = 2
)

test_data = torchvision.datasets.MNIST(
    root = './mnist',
    train = False,
    transform = torchvision.transforms.ToTensor(),
    download = True
)

test_loader = data.DataLoader(
    dataset = test_data,
    batch_size = BATCH_SIZE,
    num_workers = 2
)

LR = 0.001

class lenet5(nn.Module):
    def __init__(self):
        super(lenet5, self).__init__()
        self.conv1 = nn.Conv2d(
            in_channels = 1,
            out_channels = 6, 
            kernel_size = 5, 
            padding = 2,
        )
        self.conv2 = nn.Conv2d(
            in_channels = 6,
            out_channels = 16,
            kernel_size = 5,
        )
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)

    def forward(self, x):
        x = func.max_pool2d(func.relu(self.conv1(x)), (2, 2))
        x = func.max_pool2d(func.relu(self.conv2(x)), (2, 2))
        x = x.view(x.size(0), -1)
        x = func.relu(self.fc1(x))
        x = func.relu(self.fc2(x))
        x = self.fc3(x)
        return x

cnn = lenet5()

optimizer = torch.optim.Adam(cnn.parameters(), lr = LR)
loss_function = nn.CrossEntropyLoss()


for epoch in range(4):
    for step, (x, y) in enumerate(train_loader):
        fx = cnn(x)
        loss = loss_function(fx, y)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        c = 0
        s = 0
        
    for (tx, ty) in test_loader:
        pred_y = torch.max(cnn(tx), 1)[1]
        c = c + sum(pred_y == ty)
        s = s + ty.size(0)
    print('loss=', float(loss), ',', 'accuracy=', float(c * 1.0 / s))


torch.save(cnn.state_dict(), 'cnn.pkl')