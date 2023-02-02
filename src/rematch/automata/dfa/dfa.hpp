#ifndef SRC_REMATCH_AUTOMATA_DFA_DFA_HPP
#define SRC_REMATCH_AUTOMATA_DFA_DFA_HPP

#include <bitset>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "automata/state_subset.hpp"

#include "factories/factories.hpp"
#include "regex/regex_options.hpp"

namespace rematch {

class VariableFactory;
class ExtendedVA;

struct BaseTransition;

class DFA {

 public:
  class State;

  struct Transition {

    struct Capture {
      std::bitset<32> S;
      State* next{nullptr};
    };

    enum Type {
      kEmpty = 0,                                                 // 0000 = 0
      kDirect = 1 << 0,                                           // 0001 = 1
      kSingleCapture = 1 << 1,                                    // 0010 = 2
      kMultiCapture = 1 << 2,                                     // 0100 = 4
      kMultiDirect = 1 << 3,                                      // 1000 = 8
      kDirectSingleCapture = kDirect | kSingleCapture,            // 0011 = 3
      kDirectMultiCapture = kDirect | kMultiCapture,              // 0101 = 5
      kMultiDirectSingleCapture = kMultiDirect | kSingleCapture,  // 1010 = 10
      kMultiDirectMultiCapture = kMultiDirect | kMultiCapture     // 1100 = 12
    };

    int type_;
    State* direct_{nullptr};
    Capture capture_;
    std::vector<Capture> captures_;
    std::vector<State*> directs_;

    // Default = EmptyTransition
    Transition() : type_(Type::kEmpty) {}

    Transition(std::bitset<32> S, DFA::State* state)
        : type_(Type::kSingleCapture), capture_({S, state}) {}

    Transition(State* state) : type_(Type::kDirect), direct_(state) {}

    void add(Capture capture) {
      if (capture.S != 0)
        add_capture(capture);
      else
        add_direct(capture.next);
    }

    void add_capture(Capture capture) {
      switch (type_) {
        case Type::kEmpty:
          type_ = kSingleCapture;
          capture_ = capture;
          break;
        case Type::kDirect:
          type_ = Type::kDirectSingleCapture;
          capture_ = capture;
          break;
        case Type::kMultiDirect:
          type_ = Type::kMultiDirectSingleCapture;
          capture_ = capture;
          break;
        case Type::kSingleCapture:
          //* Do not push_back capture_ into captures_, necessary for refcounts.
          type_ = Type::kMultiCapture;
          captures_.clear();
          captures_.push_back(capture);
          break;
        case Type::kDirectSingleCapture:
          type_ = Type::kDirectMultiCapture;
          captures_.clear();
          captures_.push_back(capture);
        case Type::kMultiDirectSingleCapture:
          //* Do push_back capture_ into captures_, necessary for refcounts.
          type_ = Type::kMultiDirectMultiCapture;
          captures_.clear();
          captures_.push_back(capture_);
          captures_.push_back(capture);
          break;
        default:
          captures_.push_back(capture);
          break;
      }
    }

    void add_direct(State* state) {
      switch (type_) {
        case Type::kEmpty:
          type_ = Type::kDirect;
          direct_ = state;
          break;
        case Type::kDirect:
          type_ = kMultiDirect;
          directs_.clear();
          directs_.push_back(state);
          break;
        case Type::kDirectSingleCapture:
          type_ = kMultiDirectSingleCapture;
          directs_.clear();
          directs_.push_back(state);
          break;
        case Type::kDirectMultiCapture:
          type_ = kMultiDirectMultiCapture;
          directs_.clear();
          directs_.push_back(state);
          break;
        case Type::kSingleCapture:
          type_ = Type::kDirectSingleCapture;
          direct_ = state;
          break;
        case Type::kMultiCapture:
          type_ = Type::kDirectMultiCapture;
          captures_.push_back(capture_);
          direct_ = state;
          break;
        default:  // kMultiDirect, kMultiDirectSingleCapture, kMultiDirectMultiCapture
          directs_.push_back(state);
          break;
      }
    }
  };  // end struct Transition

  using DFAStatesTable = std::unordered_map<std::vector<bool>, State*>;
  using DFACaptureStatesTable = std::vector<std::pair<State*, std::bitset<32>>>;

  // Vector of pointers of States for resizing:
  std::vector<State*> states;
  std::vector<State*> finalStates;

  std::vector<Transition*> transitions;

  std::vector<std::string> varNames;

  DFA(ExtendedVA const& A);

  // Getter for init state
  State* init_state() { return init_state_; };

  DFACaptureStatesTable init_eval_states() { return init_eval_states_; }

  std::string pprint();

  size_t size() const { return states.size(); }

  // ---  Determinization  ---  //

#ifdef NOPT_ASCIIARRAY
  Transition next_base_transition(State* q, char a);
#else
  // @brief Compute an on-the-fly determinization
  //
  // @param q State from which to compute the next state
  // @param a Read character to follow the transitions
  // @return Transition* The correct deterministic transition from q reading a
  Transition& next_transition(State* q, char a);
#endif

  size_t tot_size() const;

 private:
  // Utility to print a transition
  void print_transition(std::ostream& os, State* from, char a, State* to,
                        std::bitset<32> S);

  Transition compute_transition(State* q, std::vector<bool> chbst);

  State* obtain_state(const StateSubset& ss);

  // The starting state of the dfa
  State* init_state_;

  ExtendedVA const& eVA_;

  std::map<std::vector<bool>, State*> dstates_table_;

  DFACaptureStatesTable init_eval_states_;

  // Access to variable and filter factory
  std::shared_ptr<VariableFactory> variable_factory_;
  std::shared_ptr<FilterFactory> ffactory_;

};  // end class DFA

struct BaseTransition {
  struct Capture {
    std::bitset<32> S;
    DFA::State* next;
  };

  std::vector<Capture> captures;

  void add(Capture c) { captures.push_back(c); }
};  // end struct BaseTransition

}  // end namespace rematch

#endif  // SRC_REMATCH_AUTOMATA_DFA_DFA_HPP
