/*******************
  Button Sequence
  Captures and reports on the successful entry of sequence. Accepts any class
  which responds to == for comparison of a successful solution.

  Written by Mike Greenberg <mg@nobulb.com>
  MIT License.
  (c)2016-2018
*******************/

#include "Cortex_Debug.h"
#include <vector>

#ifndef _BUTTON_SEQUENCE_H_
#define _BUTTON_SEQUENCE_H_

template <typename T>
class Button_Sequence
{
public:
  Button_Sequence();
  void set_solution(std::vector<T>);
  bool add_attempt(T);  // Add attempt to sequence and return bool success
  bool on_success();
  bool is_successful();
  void debug_print_memory();

private:
  void debug_print_vector(std::vector<T>);
  void reset_memory();

  bool announced_success;
  std::vector<T> m_solution;
  std::vector<T> m_memory;
};

template <typename T>
Button_Sequence<T>::Button_Sequence()
  : m_solution({})
  , m_memory({})
  , announced_success(true)
{
}

template <typename T>
void Button_Sequence<T>::set_solution(std::vector<T> solution)
{
  m_solution = solution;
  CORTEX_DEBUG_PRINT("Set solution: ");
  debug_print_vector(m_solution);
  reset_memory();
}

template <typename T>
bool Button_Sequence<T>::add_attempt(T attempt)
{
  std::vector<T> new_memory(m_memory.begin()+1, m_memory.end());
  CORTEX_DEBUG_PRINT("New memory: ");
  debug_print_vector(new_memory);
  new_memory.push_back(attempt);
  m_memory.swap(new_memory);
  CORTEX_DEBUG_PRINT("Success? ");
  CORTEX_DEBUG_PRINTLN(is_successful());
  if (is_successful()) {
    announced_success = false;
    return true;
  } else {
    return false;
  }
}

template <typename T>
bool Button_Sequence<T>::is_successful()
{
  return m_solution == m_memory;
}

template <typename T>
bool Button_Sequence<T>::on_success()
{
  if (is_successful() && announced_success == false) {
    announced_success = true;
    return true;
  } else {
    return false;
  }
}

template <typename T>
void Button_Sequence<T>::reset_memory()
{
  m_memory.clear();
  m_memory.resize(m_solution.size(), (T)(-1));
}

template <typename T>
void Button_Sequence<T>::debug_print_memory()
{
  debug_print_vector(m_memory);
}

template <typename T>
void Button_Sequence<T>::debug_print_vector(std::vector<T> m_memory)
{
#ifdef CORTEX_DEBUG
  for(int n = 0; n < m_memory.size(); n++) {
    CORTEX_DEBUG_PRINT((int)(m_memory[n]));
    CORTEX_DEBUG_PRINT(" ");
  }
  CORTEX_DEBUG_PRINTLN(".");
#endif //CORTEX_DEBUG
}

#endif //_BUTTON_SEQUENCE_H_
