#ifdef __powerpc64__

/*
 g++ -I../.. -Wall -O0 -ggdb -std=c++11  -funroll-loops -Wno-unused-parameter \
  -Wno-unknown-pragmas -Wno-unused-local-typedefs -mcpu=powerpc64le \
  -mtune=powerpc64le -DMSHADOW_USE_ALTIVEC=1 -DMSHADOW_USE_F16C=0 \
  -DMSHADOW_USE_CUDA=0 -DMSHADOW_USE_CBLAS=1 -DMSHADOW_USE_MKL=0 \
  -DMSHADOW_RABIT_PS=0 -DMSHADOW_DIST_PS=0 -DMSHADOW_USE_PASCAL=0 \
  -lm -lm -lopenblas packet.cpp -o packet
 */


//#include "../../mshadow/packet/altivec-inl.h"
// header file to use mshadow
#include "mshadow/tensor.h"

#include "mshadow/packet-inl.h"

// this namespace contains all data structures, functions
using namespace mshadow;
// this namespace contains all operator overloads
using namespace mshadow::expr;

using namespace mshadow;

int main(){
	packet::Packet<float> p = packet::Packet<float>::Fill(1.0);
	printf("Sum: %f.\n", p.Sum());
}


#else


#endif
