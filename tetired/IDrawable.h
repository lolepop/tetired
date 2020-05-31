#pragma once

template<int w, int h>
class IDrawable
{
public:
	virtual std::tuple<int, int> getOffset();
	virtual std::array<char, w*h> getPixels();
	virtual bool removeBackground();
	virtual std::vector<wchar_t> getCharMap();
};

template<int w, int h>
inline std::tuple<int, int> IDrawable<w, h>::getOffset()
{
	return std::tuple<int, int>();
}

template<int w, int h>
inline std::array<char, w* h> IDrawable<w, h>::getPixels()
{
	return std::array<char, w* h>();
}

template<int w, int h>
inline bool IDrawable<w, h>::removeBackground()
{
	return false;
}

template<int w, int h>
inline std::vector<wchar_t> IDrawable<w, h>::getCharMap()
{
	return std::vector<wchar_t>();
}
