Rendering Pipeline Specifics
===

2D Feature Requires:

    Add 2D Animation
    
    Add 2D Atlas Tool

    Add 2D Camera

    Add 2D UI Classes, Renderer

    Add Cut-scene Video playing

    Add Orthogonal Camera.

3D Feature Requires:

    Add entity system query.

    Add 3D picking in entity system. http://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms

    Add OpenGL state management using Dirty Flag pattern.

    Add Model sampler.
    
    Add crosshair rendering.

    Add AssetManager unload functionality.

    Merge asset importing: model, shader, texture into same interface.

    Linux TPS Camera issue.

Platform Feature Requires:

    Add Qt / GLFW binding.

    Add multi-threading support in engine.

    Improve Render State.

    Add Memory Pool.

    Add GameWindow class and its interaction with GameEnginePlatform to support Qt embedding.

    Add keyboard action mapping.


Handedness::GetRight() GetLeft()

Entity::GetPosition() -> Entity::GetLocalPosition()
Entity::GetWorldPosition()
    return Vector3f(mNode->mWorldTransform * Vector4f(0, 0, 0, 1));