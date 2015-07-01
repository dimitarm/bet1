/*
 * ImagePanel.h
 *
 *  Created on: Jul 12, 2014
 *      Author: I028663
 */
#include <wx/wx.h>

#ifndef IMAGEPANEL_H_
#define IMAGEPANEL_H_



class ImagePanel : public wxPanel
{
    wxImage image_;
    wxBitmap resized;
    int w, h;
    DECLARE_EVENT_TABLE();

public:
    ImagePanel(wxWindow* parent, const wxImage& image);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);
    void setImage(const wxImage& image);

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    virtual ~ImagePanel();
};




#endif /* IMAGEPANEL_H_ */
