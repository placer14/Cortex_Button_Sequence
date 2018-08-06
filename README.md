# Button_Sequence
An abstraction for capturing and reporting on a successful sequence of inputs.

# Required Libs
- std::vector
- http://github.com/placer14/cortex_debug

# Usage
```
#include <vector>
#include "Cortex_Debug.h"
#include "Button_Sequence.h"

Button_Sequence<char> sequenceMatcher = Button_Sequence<char>{};
std::vector<char> successSequence = {'3','8','7','2'};

sequenceMatcher.set_solution(successSequence);
sequenceMatcher.add_attempt('3');
sequenceMatcher.add_attempt('8');
sequenceMatcher.add_attempt('7');
if (sequenceMatcher.on_success()) {
  // will not be true
}
sequenceMatcher.add_attempt('2');
if (sequenceMatcher.on_success()) {
  // will only be true once
  success_sound();
}
if (sequenceMatcher.is_successful()) {
  // will always be true while the memory matches the successSequence
  success_sound();
}
sequenceMatcher.reset_memory();
```
