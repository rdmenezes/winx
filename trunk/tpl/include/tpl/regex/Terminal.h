/* -------------------------------------------------------------------------
// WINX: a C++ template GUI library - MOST SIMPLE BUT EFFECTIVE
// 
// This file is a part of the WINX Library.
// The use and distribution terms for this software are covered by the
// Common Public License 1.0 (http://opensource.org/licenses/cpl.php)
// which can be found in the file CPL.txt at this distribution. By using
// this software in any fashion, you are agreeing to be bound by the terms
// of this license. You must not remove this notice, or any other, from
// this software.
// 
// Module: tpl/regex/Terminal.h
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2006-8-13 9:41:58
// 
// $Id$
// -----------------------------------------------------------------------*/
#ifndef TPL_REGEX_TERMINAL_H
#define TPL_REGEX_TERMINAL_H

#ifndef TPL_REGEX_BASIC_H
#include "Basic.h"
#endif

#ifndef STDEXT_CHARTYPE_H
#include "../../../stdext/include/stdext/CharType.h"
#endif

NS_TPL_BEGIN

// -------------------------------------------------------------------------
// class BasicMatchCh

template <class PredT>
class BasicMatchCh // Match a Char
{
private:
	PredT m_pred;

public:
	BasicMatchCh() {}
	
	template <class T1>
	BasicMatchCh(const T1& x) : m_pred(x) {}

	template <class SourceT, class ContextT>
	bool TPL_CALL match(SourceT& ar, ContextT& context)
	{
		typename SourceT::int_type c = ar.peek();
		if (m_pred(c))
		{
			ar.get();
			return true;
		}
		return false;
	}
};

// -------------------------------------------------------------------------
// function ch

// Usage: ch<'a'>()
// Note: Its function is same as ch('a').

template <int m_c>
class EqCh0
{
public:
	__forceinline bool TPL_CALL operator()(int c) const {
		return m_c == c;
	}
};

template <int m_c> 
__forceinline
Exp<BasicMatchCh<EqCh0<m_c> > > TPL_CALL ch() {
	return Exp<BasicMatchCh<EqCh0<m_c> > >();
}

// -------------------------------------------------------------------------
// function ch()

// Usage: ch('a')
// Sorry that we can't use 'a' directly instead of ch('a') in all case.

class EqCh
{
private:
	int m_c;

public:
	EqCh(int c) : m_c(c) {}

	bool TPL_CALL operator()(int c) const {
		return m_c == c;
	}
};

typedef BasicMatchCh<EqCh> MatchCh;

template <class CharT> 
__forceinline
Exp<MatchCh> TPL_CALL ch(const CharT x) {
	return Exp<MatchCh>(x);
}

#define TPL_REGEX_CH_OP1_(op, Op, CharT)											\
template <class T2> __forceinline													\
Exp< Op<MatchCh, T2> > TPL_CALL operator op(CharT x, const Exp<T2>& y)				\
	{ return ch(x) op y; }															\
template <class T1> __forceinline													\
Exp< Op<T1, MatchCh> > TPL_CALL operator op(const Exp<T1>& x, CharT y)				\
	{ return x op ch(y); }

#define TPL_REGEX_CH_OP_(op, Op)													\
	TPL_REGEX_CH_OP1_(op, Op, char)

// -------------------------------------------------------------------------
// function blank, alpha, ...

// Usage: blank()		--- means: matching ONE Writespace Character
// Usage: alpha()		--- means: matching ONE Alpha Character
// Usage: ...

typedef BasicMatchCh<std::CharType::IsBlank> Blank;
typedef BasicMatchCh<std::CharType::IsAlpha> Alpha;
typedef BasicMatchCh<std::CharType::IsLower> LowerAlpha;
typedef BasicMatchCh<std::CharType::IsUpper> UpperAlpha;
typedef BasicMatchCh<std::CharType::IsDigit> Digit;
typedef BasicMatchCh<std::CharType::IsXDigit> XDigit;
typedef BasicMatchCh<std::CharType::IsEOL> EOL;

typedef BasicMatchCh<std::CharType::IsCSymbolFirstChar> CSymbolFirstChar;
typedef BasicMatchCh<std::CharType::IsCSymbolNextChar> CSymbolNextChar;

inline Exp<Blank> TPL_CALL blank() {
	return Exp<Blank>();
}

inline Exp<Alpha> TPL_CALL alpha() {
	return Exp<Alpha>();
}

inline Exp<LowerAlpha> TPL_CALL lower() {
	return Exp<LowerAlpha>();
}

inline Exp<UpperAlpha> TPL_CALL upper() {
	return Exp<UpperAlpha>();
}

inline Exp<Digit> TPL_CALL digit() {
	return Exp<Digit>();
}

inline Exp<XDigit> TPL_CALL xdigit() {
	return Exp<XDigit>();
}

inline Exp<EOL> TPL_CALL eol() {
	return Exp<EOL>();
}

// -------------------------------------------------------------------------
// $Log: $

NS_TPL_END

#endif /* TPL_REGEX_TERMINAL_H */
