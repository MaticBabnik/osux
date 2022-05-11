#include "SliderTestScene.hxx"

SliderTestScene::SliderTestScene() {

}

void SliderTestScene::Activate() {
    Scene::Activate();
    for (int i = 0; i<32; i++) {
        this->points[i].x = cos(i*0.2)*200 + 250;
        this->points[i].y = sin(i*0.2)*200 + 250;

    }
}

void SliderTestScene::Render() {
    auto r = Engine::getRenderer();

    sux_thick_aa_line_mul(r,this->points,32,20,0xffffffff);
    sux_thick_aa_line_mul(r,this->points,32,18,0xff000000);

    EntityCollection::Render();
}
