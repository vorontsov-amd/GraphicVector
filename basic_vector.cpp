#include "basic_vector.h"

BasicVector::BasicVector(double x, double y, const SystemCoord& sys) :
    cx(sys.ce1.cx * x + sys.ce2.cx * y + sys.cstart_point.cx),
    cy(sys.ce1.cy * x + sys.ce2.cy * y + sys.cstart_point.cy)
    {}

double BasicVector::length() 
{ 
    if (std::isnan(clen))
    {
        clen = std::sqrt(cx * cx + cy * cy);
    }
    return clen;
}

void BasicVector::SetX(double x, const SystemCoord& sys)
{
    cx = sys.ce1.cx * x + sys.ce2.cx * cy + sys.cstart_point.cx;
    clen = NAN;
}

void BasicVector::SetY(double y, const SystemCoord& sys)
{
    cy = sys.ce1.cy * cx + sys.ce2.cy * y + sys.cstart_point.cy;
    clen = NAN;
}

BasicVector& BasicVector::operator+=(const BasicVector& rvec)
{
    cx += rvec.cx;
    cy += rvec.cy;
    clen = NAN;
    return *this;
}

BasicVector& BasicVector::operator-=(const BasicVector& rvec)
{
    cx -= rvec.cx;
    cy -= rvec.cy;
    clen = NAN;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const BasicVector& vec)
{
    return out << "{ " << vec.cx << ", " << vec.cy << " }";
}

std::istream& operator>>(std::istream& in, BasicVector& vec)
{
    return in >> vec.cx >> vec.cy;
}