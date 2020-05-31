#include <iostream>
#include <vector>
#include "svg.h"
using namespace std;
void svg_rect(double x, double y, double width, double height,string stroke = "black",string fill = "black")
{
    cout << "<rect x='"<<x<< "' y='" <<y<<"' width='" <<width <<"' height='" <<height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"'/>";
}

void
svg_text(double left, double baseline, string text) {
      cout << "<text x='" << left << "' y='" << baseline <<"'>" <<text <<"</text>";
}

void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}
void max_height(const vector<size_t>& bins,double& maximum)
{maximum=bins[0];
for (size_t bin : bins)
{    if (bin > maximum) {
            maximum = bin;
        }
    }
    }

// изменил определение функции, добавил string stroke, передача в svg_rect
void
show_histogram_svg(const vector<size_t>& bins, string stroke, string info) {
const auto IMAGE_WIDTH = 1000;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 10;
double maximum;
max_height(bins,maximum);
size_t IMAGE_HEIGHT=(maximum*BLOCK_WIDTH)+30;
double top = IMAGE_HEIGHT-20;
svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
double TEXT_WIDTH=50;
for (size_t bin : bins)
{

const double bin_width = BLOCK_WIDTH * bin;

svg_text(TEXT_WIDTH+(BIN_HEIGHT/4.0), top + TEXT_BASELINE, to_string(bin));
    svg_rect(TEXT_WIDTH, top-bin_width, BIN_HEIGHT, bin_width ,stroke,"#aab5ff");
TEXT_WIDTH+=BIN_HEIGHT;



}

svg_text(TEXT_WIDTH, top + TEXT_BASELINE, info);
    svg_end();
}
