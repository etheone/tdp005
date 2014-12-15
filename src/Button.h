/*
 * Button.h
 *
 *  Created on: 11 dec 2014
 *      Author: joagy323
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#include "Image.h"

class Button : public Image
{
public:
	Button(const double& x, const double& y,
		   const int& w, const int& h,
		   SDL_Texture*& texture);
	~Button();

	bool in_button_area(const int& x, const int& y);

};

#endif /* SRC_BUTTON_H_ */
