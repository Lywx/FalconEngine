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

++ Added model sampler.
++ Added more members in Light class.

