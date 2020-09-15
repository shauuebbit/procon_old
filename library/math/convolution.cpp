#include <complex>
#include <vector>

#include "fast_fourier_transform.cpp"

std::vector<std::complex<double>> convolute(std::vector<std::complex<double>> signal1, std::vector<std::complex<double>> signal2) {
  int length = signal1.size() + signal2.size() + 1;
  int l = 1;
  for (; l < length; l <<= 1);

  signal1.resize(l); signal2.resize(l);

  fft(signal1); fft(signal2);

  for (int i = 0; i < l; i++) {
    signal1[i] *= signal2[i];
  }

  ifft(signal1);
  signal1.resize(length);

  return signal1;
}

int main(){
}

