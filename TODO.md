Rendering Pipeline Specifics
===

Add OpenGL state to render state.

++ Modified BitmapFontRenderer to use current rendering pipeline.
++ Modified BitmapFontRenderer::DrawText.
++ Modified BitmapFontRenderer::PrepareString

++ VisualQuad constructor is not done yet. Added VisualQuad related code to 
support multiple buffer switching without switch vertex format.

++ Added more flexible Renderer API for DrawPrimitive, Draw.
++ Added more API in the vertex buffer and index buffer so that you are allowed to initialize them later and reuse them.
++ Fixed Renderer.Draw.
++ Fixed BitmapFontRenderer::PrepareString and correctly fill text buffer.

++ Added texture / sampler binding into uniform?

---

++ Separated Mesh and aiMesh using factory pattern or something else.
++ Merged Buffer element and primitive element number information.
++ Encapsulated Assimp layer in Content Project.
++ Rewrote Mesh, Model, Node class to conform the new Primitive abstraction.
++ Added texture operation in Model class.
++ Removed texture information in Mesh to somewhere else.
++ Rewrote mesh loading in new Primitive abstraction so that texture and sampler would be in corresponding visual effect instance.

--
Optimized the LoadMaterialTexture.
Changed AssetManager to use file name as index for asset look up.
Fixed AssetProcess for Model baking.