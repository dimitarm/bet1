/*
 * Graphic.cpp
 *
 *  Created on: Jun 28, 2014
 *      Author: dimitar
 */

#include "Graphic.h"
#include <iostream>
#include <algorithm>
using namespace std;
//600x320 allowed big
//offset 20, 18
//600x160 allowed small
//offset 20, 18
Graphic::Graphic(const wxImage& initial_image, unsigned int offset_x,
		unsigned int offset_y, unsigned int allowed_width,
		unsigned int allowed_height, unsigned int x_limit, unsigned int y_limit,
		const std::vector<wxColor>& colors) :
		offset_x_(offset_x), offset_y_(offset_y), colors_(
				colors), serie_count_(
				colors.size()), image_(initial_image) {
	x_const_ = float(allowed_width) / float(x_limit);
	y_const_ = float(allowed_height) / float(y_limit);

	for (unsigned int i = 0; i < serie_count_.size(); i++)
		serie_count_[i] = 0;
}

void Graphic::AddValue(int serie, float value) {
	serie_count_[serie]++;
	float y = value * y_const_;
	if (y >= image_.GetHeight())
		y = image_.GetHeight() - 1;
	float x = serie_count_[serie] * x_const_;
	setPixel(x, y, colors_[serie]);
}

void Graphic::setPixel(unsigned int x, unsigned int y, const wxColor& color) {
	x += offset_x_; y += offset_y_;
	if (y >= image_.GetHeight() or y < 0 or x >= image_.GetWidth() or x < 0) {
		return;
	}
	y = image_.GetHeight() - y - 1;
	unsigned char* raw = image_.GetData();

	raw[y * image_.GetWidth() * 3 + x * 3] = color.Red();
	raw[y * image_.GetWidth() * 3 + x * 3 + 1] = color.Green();
	raw[y * image_.GetWidth() * 3 + x * 3 + 2] = color.Blue();
}

const wxImage& Graphic::getImage() const {
	return image_;
}

