#include <syntacts>

using namespace tact;

int main(int argc, char const *argv[])
{
    Session ss;
    ss.open(5);
    sleep(1);

    Signal sig = Sine(440);

    Spatializer sp(&ss);

    std::cout << sp.getChannelCount() << std::endl;

    // set up channels
    int chs = ss.getChannelCount();
    float spc = 1.0f / (chs - 1);
    for (int i = 0; i < ss.getChannelCount(); ++i) 
        sp.setPosition(i, i * spc);

    std::cout << sp.getChannelCount() << std::endl;

    // set up target
    sp.setTarget(0.0);
    sp.setRadius(0.5);
    
    // play
    sp.play(sig);

    // do something cool
    float t = 0;
    while (t < 10) {
        float x = 0.5f + 0.5f * std::sin(2*PI*t);
        sp.setTarget(x);
        sleep(0.01f);
        t += 0.01f;
    }

    std::cout << "Finished!" << std::endl;
    return 0;
}
