// include/BPAST/bpast.hpp
#pragma once

#include <BPAST/core/meowgine.hpp>
#include <BPAST/graphics/meowxture.hpp>
#include <BPAST/scene/meowscene.hpp>

// i gotta do this so people dont have to start meowing just to
// get a scene going or sum
namespace bpast {
    using Engine  = meowgine;
    using Texture = meowxture;
    using Scene   = meowscene;
    using Camera  = meowmera;
    using Shader  = meowder;
    using Window  = meowindow;
    using SceneObject = meowObject;
    using Player = kittycat;
}
