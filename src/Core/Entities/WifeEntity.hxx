#pragma once

#include "../../include.hxx"
#include "../Engine.hxx"

namespace Core {

/*
 * I LOVE MY WIFE
 *
 * https://www.youtube.com/watch?v=iUsecpG2bWI
 */
    /**
     * @summary DOKO MITENDAYO! DOKO MITENDA!
     * @see https://www.youtube.com/watch?v=iUsecpG2bWI
     */
    class WifeEntity : public Core::Entity {
    public:
        WifeEntity();

        void Render() override;

    protected:
        SDL_Texture *fbk;
    };


}