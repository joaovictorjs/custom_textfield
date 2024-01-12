#include <wx/wx.h>

#include "text_field.h"

class Window : public wxFrame {
public:
  Window()
      : wxFrame(nullptr, wxID_ANY, "Custom text field", wxDefaultPosition,
                wxSize(800, 600)) {
    Centre();

    wxPanel *panel = new wxPanel(this, wxID_ANY);

    TextField *tf =
        new TextField(panel, wxID_ANY, wxPoint(20, 20), wxSize(80, 40));
  }
};

class Application : public wxApp {
public:
  bool OnInit() override {
    Window *win = new Window();
    return win->Show(true);
  }
};

wxIMPLEMENT_APP(Application);
