#include "Node.h"

bool EmptyNode :: Evaluate(const Date& date, const string& event) const {
	return true;
}

bool DateComparisonNode:: Evaluate(const Date& date, const string& event) const {
        switch (cmp_){
        case Comparison::Less:
            return date < date_;
        case Comparison::LessOrEqual:
            return date <= date_;
        case Comparison::Greater:
            return date > date_;
        case Comparison::GreaterOrEqual:
            return date >= date_;
        case Comparison::Equal:
            return date == date_;
        case Comparison::NotEqual:
            return date != date_;
        }
	    return false;
}

bool EventComparisonNode:: Evaluate(const Date& date, const string& event) const {
    switch (cmp_) {
    case Comparison::Equal:
        return event == event_;
    case Comparison::NotEqual:
        return event != event_;
    }
    return false;
}

bool LogicalOperationNode:: Evaluate(const Date& date, const string& event) const {
    switch (lo_) {
    case LogicalOperation::Or:
        return lhs_->Evaluate(date, event) || rhs_->Evaluate(date, event);
    case LogicalOperation::And:
        return lhs_->Evaluate(date, event) && rhs_->Evaluate(date, event);
    }
    return false;
}
