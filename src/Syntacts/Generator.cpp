#include <Syntacts/Generator.hpp>
#include "Helpers.hpp"

namespace tact {

Generator::Generator() :
    m_time(0.0f)
{
    
}

Generator::~Generator() {
    // do nothing by default
}

float Generator::getTime() const {
    return m_time;
}

float Generator::nextSample() {
    float sample = onSample(m_time);
    m_time += SAMPLE_LENGTH;
    return sample;
}

void Generator::reset() {
    m_time = 0.0f;
}

} // namespace tact