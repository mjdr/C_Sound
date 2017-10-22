#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#define SAMPLE_RATE 44100 //Hz
#define TIME 10.0          //sec

#define PI 3.141592



float osc_sin(float t){
 return sin(2.*PI * t);
}
float osc_sqr(float t){
 t = fmod(t,1.0f);
 return t < 0.5 ? -1 : 1;
}
float osc_saw(float t){
 t = fmod(t,1.0f);
 return 2.f * t - 1.;
}

float osc_inv_saw(float t){
 t = fmod(t, 1.0f);
 return 1. - 2.f * t;
}


float note(float n){
 return 440.f * powf(2,(n-24)/12.);
}


float voice0(float t){
 return 0.7 * osc_sin(t) + 0.3 * osc_sin(2.f * t);
}





float exp_curve(float t , float k){
 if(t < 0.f) return 0.f;
 return expf(-k*t);
}
float lin_change(float start, float end, float t){
 if(t < 0.f || t > 1.f) return 0.f;
 return start * (1.f - t) + end * t;
}




float ar(float rise, float fall, float t){
 if(t < 0.f) return 0.f;
 if(t < rise) return t/rise;
 t -= rise;
 
 return exp(-t*fall);
 //if(t < fall) return 1.f - t/fall;
 //return 0.f;
}

float temp0(float t){
 int p = (int)(4.f*t);
 t = fmod(t , .25);
 p %= 4;
 int n = 0;
 
 if(p == 0) n = 15;
 if(p == 1) n = 21;
 if(p == 2) n = 19;
 if(p == 3) n = 21; 
 
 return ar(0.07,20,t) * voice0(note(n)*t);
}

float sound(float t){
 
 return temp0(t);
}

int main(){
 
 int64_t nSamples = (uint64_t)(SAMPLE_RATE * TIME);
 
 for(uint64_t i = 0;i < nSamples;i++){
  int16_t sample = (int16_t)(sound(((float)i)/SAMPLE_RATE) * 32000);
  write(1, &sample, sizeof(int16_t));
 }
 return 0;
}
