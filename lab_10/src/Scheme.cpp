#include "Scheme.hpp"

Scheme::Scheme(int capacity) : current_position(0) {
    figures_ = new Figure*[capacity];
}

Scheme::~Scheme() {
    int current_element = 0;
    while (current_element < current_position) {
        delete figures_[current_element];
        ++current_element;
    }
    delete [] figures_;
}

void Scheme::push_back_figure(Figure *fg) {
    figures_[current_position] = fg;
    ++current_position;
}

void Scheme::remove_figure(int id) {
    int position = find_element(id);

    delete figures_[position];
    --current_position;

    while (position < current_position) {
        figures_[position] = figures_[position + 1];
        ++position;
    }
}

void Scheme::print_all_figures() {
    for (int k = 0; k < current_position; ++k) {
        figures_[k]->print();
    }
}

void Scheme::zoom_figure(int id, int factor) {
    figures_[find_element(id)]->zoom(factor);
}

Figure * Scheme::is_inside_figure(int x, int y) {
    int position = 0;
    while (position < current_position) {
        if (figures_[position]->is_inside(x, y)) {
            return figures_[position];
        }
        ++position;
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    figures_[find_element(id)]->move(new_x, new_y);
}

int Scheme::find_element(int id) const {
    int position = 0;
    while (position < current_position) {
        if (figures_[position]->get_id() == id) {
            return position;
        }
        ++position;
    }
    return -1;
}