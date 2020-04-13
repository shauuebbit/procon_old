#include<complex>
#include<vector>

void fft(std::vector<std::complex<double>>& signal){
  int length = signal.size();
  
  for(int i = 0, j = 0; i < (length >> 1); i += 2){
    if(i < j){
      std::swap(signal[i], signal[j]);
      std::swap(signal[i + (length >> 1) + 1], signal[j + (length >> 1) + 1]);
    }
    std::swap(signal[i + (length >> 1)], signal[j + 1]);

    for(int k = length >> 2; k > (j ^= k); k >>= 1);
  }

  for(int k = 1; k < length; k <<= 1){
    std::complex<double> rot = std::polar(1.0, -M_PI / (double)k * i);
    std::complex<double> w = 1.0;
    for(int i = 0; i < k; i++){
      for(int j = 0; j < length; j += k << 1){
        std::complex<double> z = signal[i + j + k] * w;
        signal[i + j + k] = signal[i + j] - z;
        signal[i + j] += z;
      }
      w *= rot;
    }
  }
}

void ifft(std::vector<std::complex<double>>& signal){
  int length = signal.size();
  double length_inv = 1.0 / (double)length;
  for(int k = 0; k < length; k++){
    signal[k] = std::conj(signal[k]) * length_inv;
  }

  fft(signal);

  for(int n = 0; n < length; n++){
    signal[n] = std::conj(signal[n]);
  }
}

