/*!
 *  Copyright (c) 2014 by Contributors
 * \file altivec-inl.h
 * \brief support of altivec packet optimization of some operations.
 */
#ifndef MSHADOW_PACKET_ALTIVEC_INL_H_
#define MSHADOW_PACKET_ALTIVEC_INL_H_

#include <altivec.h>
#undef bool
#undef vector
#undef pixel

#include "../base.h"
#include "../packet-inl.h"

namespace mshadow {
namespace packet {
template<>
struct Packet<float, kALTIVEC> {
 public:
  /*! \brief number of float in vector */
  static constexpr index_t size = 4;
  /*! \brief The internal data */
  __vector float data_;
  // enable default copy constructor
  Packet(void) {}
  // constructor from the intrinsic type
  explicit Packet(__vector float data) : data_(data) {}
  // create a fill with the target value s
  MSHADOW_CINLINE static Packet<float, kALTIVEC> Fill(float s) {
	  printf("Huaxin debug: %s.\n", __FUNCTION__);
    return Packet<float, kALTIVEC>(vec_splats(s));
  }
  // load from address
  MSHADOW_CINLINE static Packet<float, kALTIVEC> Load(const float* src) {
	  printf("Huaxin debug: %s.\n", __FUNCTION__);
    return Packet<float, kALTIVEC>(vec_vsx_ld(0, src));
  }
  // load from address
  MSHADOW_CINLINE static Packet<float, kALTIVEC> LoadUnAligned(const float* src) {
	  printf("Huaxin debug: %s.\n", __FUNCTION__);
    return Packet<float, kALTIVEC>(vec_vsx_ld(0, src));
  }
  // fill it with value s
  MSHADOW_CINLINE Packet<float, kALTIVEC>& operator=(float s) {
	  printf("Huaxin debug: %s.\n", __FUNCTION__);
    data_ = vec_splats(s);
    return *this;
  }
  // store data into dst
  MSHADOW_CINLINE void Store(float* dst) const {
	  printf("Huaxin debug: %s.\n", __FUNCTION__);
    vec_vsx_st(data_, 0, dst);
  }
  // get the sum of all contents
  MSHADOW_CINLINE float Sum() const {
	  printf("Huaxin debug: %s.\n", __FUNCTION__);
    __vector float ans = vec_add(data_, vec_sld(data_, data_, 12));
    ans = vec_add(ans, vec_sld(ans, ans, 8));
    return vec_extract(ans, 0);
  }
};

/*! \brief vector real type for float */
template<>
struct Packet<double, kALTIVEC> {
  /*! \brief number of float in vector */
  static constexpr index_t size = 2;
  // internal data
  __vector double data_;
  // constructor
  Packet(void) {}
  explicit Packet(__vector double data) : data_(data) {}
  // create a fill with the target value s
  MSHADOW_CINLINE static Packet<double, kALTIVEC> Fill(double s) {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
    return Packet<double, kALTIVEC>(vec_splats(s));
  }
  // load from address
  MSHADOW_CINLINE static Packet<double, kALTIVEC> Load(const double* src) {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
    return Packet<double, kALTIVEC>(vec_vsx_ld(0, src));
  }
  MSHADOW_CINLINE static Packet<double, kALTIVEC> LoadUnAligned(const double* src) {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
    return Packet<double, kALTIVEC>(vec_vsx_ld(0, src));
  }
  // fill it with value s
  MSHADOW_CINLINE Packet<double, kALTIVEC>& operator=(double s) {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
    data_ = vec_splats(s);
    return *this;
  }
  // store data into dst
  MSHADOW_CINLINE void Store(double* dst) const {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
    vec_vsx_st(data_, 0, dst);
  }
  // get sum of all content
  inline double Sum(void) const {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
	__vector double ans = vec_add(data_, vec_sld(data_, data_, 8));
/*
#if defined(__GNUG__) && !defined(__clang__)
    __vector double ans = vec_add(data_, vec_sld(data_, data_, 8));
#else
    vector double ans = vec_add(data_, vec_sldw(data_, data_, 2));
#endif
*/
    return vec_extract(ans, 0);
  }
};

MSHADOW_CINLINE Packet<float, kALTIVEC> operator+(const Packet<float, kALTIVEC>& lhs,
                                                    const Packet<float, kALTIVEC>& rhs) {
  printf("Huaxin debug: %s.\n", __FUNCTION__);
  return Packet<float, kALTIVEC>(vec_add(lhs.data_, rhs.data_));
}

MSHADOW_CINLINE Packet<double, kALTIVEC> operator+(const Packet<double, kALTIVEC>& lhs,
                                                     const Packet<double, kALTIVEC>& rhs) {
  printf("Huaxin debug: %s.\n", __FUNCTION__);
  return Packet<double, kALTIVEC>(vec_add(lhs.data_, rhs.data_));
}

MSHADOW_CINLINE Packet<float, kALTIVEC> operator-(const Packet<float, kALTIVEC>& lhs,
                                                    const Packet<float, kALTIVEC>& rhs) {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
  return Packet<float, kALTIVEC>(vec_sub(lhs.data_, rhs.data_));
}

MSHADOW_CINLINE Packet<double, kALTIVEC> operator-(const Packet<double, kALTIVEC>& lhs,
                                                     const Packet<double, kALTIVEC>& rhs) {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
  return Packet<double, kALTIVEC>(vec_sub(lhs.data_, rhs.data_));
}

MSHADOW_CINLINE Packet<float, kALTIVEC> operator*(const Packet<float, kALTIVEC>& lhs,
                                                    const Packet<float, kALTIVEC>& rhs) {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
  return Packet<float, kALTIVEC>(vec_mul(lhs.data_, rhs.data_));
}

MSHADOW_CINLINE Packet<double, kALTIVEC> operator*(const Packet<double, kALTIVEC>& lhs,
                                                     const Packet<double, kALTIVEC>& rhs) {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
  return Packet<double, kALTIVEC>(vec_mul(lhs.data_, rhs.data_));
}


MSHADOW_CINLINE Packet<float, kALTIVEC> operator/(const Packet<float, kALTIVEC>& lhs,
                                                    const Packet<float, kALTIVEC>& rhs) {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
  return Packet<float, kALTIVEC>(vec_div(lhs.data_, rhs.data_));
}

MSHADOW_CINLINE Packet<double, kALTIVEC> operator/(const Packet<double, kALTIVEC>& lhs,
                                                     const Packet<double, kALTIVEC>& rhs) {
	printf("Huaxin debug: %s.\n", __FUNCTION__);
  return Packet<double, kALTIVEC>(vec_div(lhs.data_, rhs.data_));
}

}  // namespace packet
}  // namespace mshadow

#endif /* MSHADOW_PACKET_ALTIVEC_INL_H_ */
