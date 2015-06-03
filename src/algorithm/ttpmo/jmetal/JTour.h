//  ArrayReal.h
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef JTOUR_h
#define JTOUR_h

#include "core/Variable.h"
#include "core/Problem.h"
#include "util/PseudoRandom.h"
#include <sstream>
#include <vector>

/**
 * Class implementing a decision variable representing an array of real values.
 * The real values of the array have their own bounds.
 */
class JTour : public Variable {

private:




public:

  std::vector<int> v;
  Problem * problem_;

  JTour();
  JTour(vector<int> v);
  JTour(int size);
  JTour(int size, Problem * problem);
  JTour(JTour*);

  Variable * deepCopy();
  int getLength();
  double getValue(int index);
  void setValue(int index, double value);
  double getLowerBound(int index);
  double getUpperBound(int index);
  string toString();

  void setValue(double value);
  double getValue();
  double getLowerBound();
  double getUpperBound();
  int const& operator[](int i) const {
    return v[i];
  }

};

#endif
