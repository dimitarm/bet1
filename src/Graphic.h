/*
 * Graphic.h
 *
 *  Created on: Jun 28, 2014
 *      Author: dimitar
 */
#include <vector>
#include <cfloat>
#include <wx/image.h>
#include <wx/colour.h>

#ifndef GRAPHIC_H_
#define GRAPHIC_H_

using namespace std;

class Graphic {
public:
	Graphic(const wxImage& initial_image,
			unsigned int offset_x, unsigned int offset_y,
			unsigned int allowed_width, unsigned int allowed_height, unsigned int x_limit, unsigned int y_limit, const std::vector<wxColor>& colors);
	virtual ~Graphic() {
	}
	;

	void AddValue(int serie, float value);
	const wxImage& getImage() const;

private:
	void renew_image();
	void setPixel(unsigned int x, unsigned int y, const wxColor& color);

	unsigned int offset_x_;
	unsigned int offset_y_;
	float x_const_;
	float y_const_;
	std::vector<wxColor> colors_;
	std::vector<unsigned int> serie_count_;
	wxImage image_;
};

#endif /* GRAPHIC_H_ */
