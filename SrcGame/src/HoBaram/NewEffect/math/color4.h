

#ifndef _COLOR4_H
#define _COLOR4_H

#include "mathGlobal.h"

#include "color3.h"

struct color4
{
	union {
		struct 
		{
			float r, g, b, a; 
        };
		float c[4];
	};

	color4(){}

	color4( float inR, float inG, float inB, float inA ) :
		r( inR ), g( inG ), b( inB ), a( inA )
	{
	}

	color4( const color3& in, float alpha = 1.f )
	{
		r = in.r;
		g = in.g;
		b = in.b;
		a = alpha;
	}

	color4( unsigned long color )
	{
		b = (float)(color&255) / 255.f;
		color >>= 8;
		g = (float)(color&255) / 255.f;
		color >>= 8;
		r = (float)(color&255) / 255.f;
		color >>= 8;
		a = (float)(color&255) / 255.f;
	}


	void Assign( float inR, float inG, float inB, float inA )
	{
		r = inR;
		g = inG;
		b = inB;
		a = inA;
	}

	unsigned long MakeDWord()
	{
		unsigned long iA = (int)(a * 255.f ) << 24;
		unsigned long iR = (int)(r * 255.f ) << 16;
		unsigned long iG = (int)(g * 255.f ) << 8;
		unsigned long iB = (int)(b * 255.f );
		return iA | iR | iG | iB;
	}

	unsigned long MakeDWordSafe()
	{
		color4 temp = *this;
		temp.Sat();
		return temp.MakeDWord();
	}

	
	void Sat()
	{
		if( r > 1 ) 
			r = 1.f;
		if( g > 1 ) 
			g = 1.f;
		if( b > 1 ) 
			b = 1.f;
		if( a > 1 ) 
			a = 1.f;
		if( r < 0 ) 
			r = 0.f;
		if( g < 0 ) 
			g = 0.f;
		if( b < 0 ) 
			b = 0.f;
		if( a < 0 ) 
			a = 0.f;
	}

	color4& operator += ( const color4& in );
	color4& operator -= ( const color4& in );
	color4& operator *= ( const color4& in );
	color4& operator /= ( const color4& in );
	color4& operator *= ( const float& in );
	color4& operator /= ( const float& in );

	
	static const color4 Black;
	static const color4 Gray;
	static const color4 White;
	static const color4 Red;
	static const color4 Green;
	static const color4 Blue;
	static const color4 Magenta;
	static const color4 Cyan;
	static const color4 Yellow;

};




inline color4& color4::operator += ( const color4& in )
{
	r += in.r;   
	g += in.g;   
	b += in.b;
	a += in.a;
	return *this;
}



inline color4& color4::operator -= ( const color4& in )
{
	r -= in.r;   
	g -= in.g;   
	b -= in.b;
	a -= in.a;
	return *this;
}



inline color4& color4::operator *= ( const color4& in )
{
	r *= in.r;   
	g *= in.g;   
	b *= in.b;
	a *= in.a;
	return *this;
}



inline color4& color4::operator /= ( const color4& in )
{
	r /= in.r;   
	g /= in.g;   
	b /= in.b;
	a /= in.a;
	return *this;
}



inline color4& color4::operator *= ( const float& in )
{
	r *= in;   
	g *= in;   
	b *= in;
	a *= in;
	return *this;
}



inline color4& color4::operator /= ( const float& in )
{
	float inv = 1.f / in;
	r *= inv;   
	g *= inv;   
	b *= inv;
	a *= inv;
	return *this;
}



inline color4 operator+(color4 const &a, color4 const &b)
{
	return color4
	(
		a.r+b.r,
		a.g+b.g,
		a.b+b.b,
		a.a+b.a
	);
}; 
 


inline color4 operator-(color4 const &a, color4 const &b)
{
	return color4
	(
		a.r-b.r,
		a.g-b.g,
		a.b-b.b,
		a.a-b.a
	);
}; 



inline color4 operator*(color4 const &a, float const &b)
{
	return color4
	(
		a.r*b,
		a.g*b,
		a.b*b,
		a.a*b
	);
}; 



inline color4 operator*(float  const &a, color4 const &b)
{
	return color4
	(
		a*b.r,
		a*b.g,
		a*b.b,
		a*b.a
	);
}; 



inline color4 operator/(color4 const &a, float const &b)
{
	float inv = 1.f / b;
	return color4
	(
		a.r*inv,
		a.g*inv,
		a.b*inv,
		a.a*inv
	);
}; 


inline color4 operator/(color4 const &a, color4 const &b)
{
	return color4
	(
		a.r / b.r,
		a.g / b.g,
		a.b / b.b,
		a.a / b.a
	);
}; 


inline color4 operator*(color4 const &a, color4 const &b)
{
	return color4
	(
		a.r * b.r,
		a.g * b.g,
		a.b * b.b,
		a.a * b.a
	);
}; 



inline bool operator==(color4 const &a, color4 const &b)
{
	if(FastFabs(a.r-b.r)<EPSILON)
		if(FastFabs(a.g-b.g)<EPSILON)
			if(FastFabs(a.b-b.b)<EPSILON)
				if(FastFabs(a.a-b.a)<EPSILON)
					return true;
	return false;
};


#endif 
