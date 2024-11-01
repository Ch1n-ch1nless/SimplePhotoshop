#include "bar.hpp"

using namespace ps;

void ABarButton::setState(State state)
{
    state_ = state;
}

psapi::IBarButton::State ABarButton::getState() const
{
    return state_;
}