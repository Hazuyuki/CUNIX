import torch
import torchvision
import torch.nn as nn
import torch.nn.functional as func

def writeto(pk, f):
    s = pk.shape
    for elem in s:
        f.write(str(int(elem)) + ' ')
    f.write('\n')
    temp = pk.reshape(-1)
    for elem in temp:
        f.write(str(float(elem)) + ' ')
    f.write('\n')



ckp = torch.load('cnn.pkl')
with open('cnn.cm', 'w') as f:
    f.write('Conv\n')
    f.write('2 1\n') #padding stride
    writeto(ckp['conv1.weight'], f)
    writeto(ckp['conv1.bias'], f)
    f.write('ReLU\n')
    f.write('MaxP\n')
    f.write('2 2\n')
    f.write('Conv\n')
    f.write('0 1\n')
    writeto(ckp['conv2.weight'], f)
    writeto(ckp['conv2.bias'], f)
    f.write('ReLU\n')
    f.write('MaxP\n')
    f.write('2 2\n')
    f.write('FC\n')
    writeto(ckp['fc1.weight'], f)
    writeto(ckp['fc1.bias'], f)
    f.write('ReLU\n')
    f.write('FC\n')
    writeto(ckp['fc2.weight'], f)
    writeto(ckp['fc2.bias'], f)
    f.write('ReLU\n')
    f.write('FC\n')
    writeto(ckp['fc3.weight'], f)
    writeto(ckp['fc3.bias'], f)
    f.write('OUTPUT\n')
