
#include "JTour.h"
#include <algorithm>


/**
 * Constructor
 */
JTour::JTour(){
  problem_ = NULL;
} // Constructor



JTour::JTour(vector<int> v):  v(v) {
}

/**
 * Constructor
 * @param size Size of the array
 */
JTour::JTour(int size) {
  for (int i = 1; i < size ; i++) {
    v.push_back(i);
  }
  std::random_shuffle(v.begin(), v.end());
  v.insert(v.begin(), 0);
} // Constructor


/**
 * Constructor
 * @param size Size of the array
 */
JTour::JTour(int size, Problem * problem) : JTour(size) {
  problem_ = problem;
} // Constructor


/**
 * Copy Constructor
 * @param arrayReal The arrayDouble to copy
 */
JTour::JTour(JTour * tour) {
  problem_ = tour->problem_;
  v = std::vector<int>(tour->v);
}
// Copy Constructor




/**
 * Creates an exact copy of a <code>BinaryReal</code> object.
 * @return The copy of the object
 */
Variable * JTour::deepCopy() {
  return new JTour(this);
} // deepCopy


/**
 * Returns the length of the arrayReal.
 * @return The length
 */
int JTour::getLength(){
  return v.size();
} // getLength


/**
 * getValue
 * @param index Index of value to be returned
 * @return the value in position index
 */
double JTour::getValue(int index) {
  if ((index >= 0) && (index < getLength()))
    return v[index] ;
  else {
    cerr << "ArrayReal.getValue: index value (" << index << ") invalid" << endl;
    exit(-1);
  } // if
} // getValue

double JTour::getValue() {
  cerr << "ERROR: ArrayReal::getValue() without index" << endl;
  exit(-1);
} // getValue


/**
 * setValue
 * @param index Index of value to be returned
 * @param value The value to be set in position index
 */
void JTour::setValue(int index, double value) {
  if ((index >= 0) && (index < getLength()))
    v[index] = value;
  else {
    cout << "ArrayReal.getValue: index value (" << index << ") invalid" << endl;
  } // if
} // setValue

void JTour::setValue(double value) {
  cout << "ERROR: ArrayReal::setValue(value) without index" << endl;
} // setValue


/**
 * Get the lower bound of a value
 * @param index The index of the value
 * @return the lower bound
 */
double JTour::getLowerBound(int index) {
  if ((index >= 0) && (index < getLength()))
    return problem_->getLowerLimit(index) ;
  else {
    cerr << "ArrayReal.getValue: index value (" << index << ") invalid" << endl;
    exit(-1);
  } // if
} // getLowerBound

double JTour::getLowerBound() {
  cerr << "ERROR: ArrayReal::getLowerBound() without index" << endl;
  exit(-1);
} // getLowerBound


/**
 * Get the upper bound of a value
 * @param index The index of the value
 * @return the upper bound
 */
double JTour::getUpperBound(int index) {
  if ((index >= 0) && (index < getLength()))
    return problem_->getUpperLimit(index);
  else {
    cerr << "ArrayReal.getValue: index value (" << index << ") invalid" << endl;
    exit(-1);
  } // if
} // getLowerBound

double JTour::getUpperBound() {
  cerr << "ERROR: ArrayReal::getUpperBound() without index" << endl;
  exit(-1);
} // getUpperBound


/**
 * Returns a string representing the object
 * @return The string
 */
string JTour::toString(){
  std::ostringstream ss;
  for (int i = 0; i < (getLength() - 1); i ++) {
    ss << v[i] << " ";
  }
  ss << v[getLength() -1];
  return ss.str();
} // toString
