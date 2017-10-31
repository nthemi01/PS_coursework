/**
*@file Sample file using the Google C++ coding standard.
*
* http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
*
* General rules:
*   - Indents are two spaces. No tabs should be used anywhere.
*   - Each line must be at most 80 characters long.
*   - Comments can be // or /* but // is most commonly used.
*   - File names should be lower_case.c or lower-case.c
*
* Note: The Google C++ coding standard is a C++ coding standard. There are
* aspects specific to C that the coding standard does not specify, and these
* exceptions are noted below.
*@auther KAI LIU
**/

#include <stdlib.h>
#include <stdbool.h>

using std::string

// For macros, use ALL_CAPS separated by underscore:
#define FLAG_FOO 0x0

// If a macro's replacement is not just a literal, enclose it in parentheses:
#define FLAG_BAZ (0x1 << 3)

// For constants, use k followed by PascalCase:
const int kStateFoo = 0;

// Type names should be PascalCase.
// Note: the Google coding standard does not specify how to format a struct
// name that has not been typedef-ed. I am following the lower_case separated
// by underscores format for now but this can be changed later.
typedef struct linked_list LinkedList;

// Enum values can either look like macros:
typedef enum {
  MODE_FOO,
  MODE_BAR,
  MODE_BAZ,
  MODE_QUX
} Mode;

// or they can look like contants:
typedef enum {
  kStateFoo,
  kStateBar,
  kStateBaz,
  kStateQux
} State;

// Names of members of structs are lower_case and separated by underscores:
typedef struct sample {
  int first_field;
  bool second_field;
  Mode mode;
  State state;
  struct sample *next;
} Sample;

// Function names are PascalCase. Opening braces come at the end of the last
// line for the function declaration rather than on the next line.
bool SampleEqual(Sample *self, Sample *other) {
  // Local variables are lower_case and separated by underscores.
  if (self == NULL && other == NULL) {
    return true;
  }

  if (self == NULL || other == NULL) {
    return false;
  }

  // For statements that span multiple lines, break after the logical operator
  // and align each line with the start of the first line.
  if (self->first_field == other->first_field &&
      self->second_field == other->second_field &&
      self->state == other->state &&
      self->mode == other->mode &&
      self->next == other->next) {
    return true;
  }
  // If the previous block ends with areturn (or break or continue), do not
  // follow it with an else.
  return false;
}

// For function declarations that span multiple lines, then align subsequent
// lines with the first parameter.
/**
 * @brief Short introduction about function SampleNew
 *
 *@param first_field used to add a number
 *@param 
 */
Sample *SampleNew(int first_field,
                  bool second_field,
                  Mode mode,
                  State state,
                  Sample *next) {
  Sample *sample = (Sample *) malloc(sizeof(*sample));
  if (sample == NULL) {
    return NULL;
  }

  memset(sample, 0, sizeof(sample));
  sample->first_field = first_field;
  sample->second_field = second_field;
  sample->mode = mode;
  sample->state = state;
  sample->next = next;
  return sample;
}

Sample *SampleClone(Sample *sample) {
  if (sample == NULL) {
    return NULL;
  }
  // For function calls that span multiple lines, align each subsequent line.
  return SampleNew(sample->first_field,
                   sample->second_field,
                   sample->mode,
                   sample->state,
                   sample->next);
}

// For function declarations (and function calls) where you cannot fit
// the parameters with the first after the opening parentheses, then align
// the parameters indented four spaces on the next line:
static void SampleDoSomethingWithALongName(
    Sample *sample,
    int parameter_with_a_long_name,
    bool another_parameter,
    int another_parameter) {
  if (sample == NULL) {
    return;
  }

  // else and else if comes after the previous closing brace and not on the
  // next line.
  bool local_variable;
  if (parameter_with_a_long_name == kStateFoo) {
    local_variable = true;
  } else {
    local_variable = false;
  }
  sample->first_parameter += another_parameter;
  sample->second_parameter |= local_variable;
}

class EventLoop : public CallbackInterface {
 public:
  typedef vector<int> IntVector;
  enum UrlTableErrors {
    ERROR_OUT_OF_MEMORY = 0,
    ERROR_MAL_INOUT,
  };
  explicit EventLoop(const int cnt);
  
  void Add(const std::string& input, Channel* output)

  int num_entries() const { return num_entries_; }

  void set_num_entries(int num_entries) { num_entries_ = num_entries; }

 private:
  DISALLOW_COPY_AND_ASSIGN(EventLoop);

  const int kDaysInWeek = 7;
  int num_entries_;
  
  Channel* channel_;
};