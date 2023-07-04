# Log for code improvement and debugging

2023/06/30 ZY
The Python script might take too much memory for Pico, will need to improve it.

2023/07/01 ZY
Increase the training dataset to 60000 samples (was 10000), but the accuracy is still ~60% (max 65% I tried). We are reaching the algorithm limit. So my algorithm is not good enough, and maybe can try adding neural layer number later.

2023/07/03 ZY
By reducing the learning factor k, the AI recognition accuracy is increased to over 90%

2023/07/05 ZY
Added scripts for multiple layers and more neurons (multiple layers one isn't finished). The accuracy is increased to 95% by making the hidden layer's neurons from 10 to 100. I believe the multi-ayer one will be even better. If we have a neural network with 2 hidden-layer, and each layer has 100 neurons, could the accuracy be > 99% ?
