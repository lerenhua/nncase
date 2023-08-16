import numpy as np

X = np.random.rand(384,8192).astype(np.float32)
WK = np.random.rand(64,8192,128).astype(np.float32) * 5 - 1

K = X @ WK



X.tofile("X.bin")
WK.tofile("WK.bin")
K.tofile("K.bin")