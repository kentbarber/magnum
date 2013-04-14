#ifndef Magnum_DebugTools_ShapeRenderer_h
#define Magnum_DebugTools_ShapeRenderer_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013 Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Class Magnum::DebugTools::ShapeRenderer, Magnum::DebugTools::ShapeRendererOptions, typedef Magnum::DebugTools::ShapeRenderer2D, Magnum::DebugTools::ShapeRenderer3D
 */

#include "Color.h"
#include "Resource.h"
#include "SceneGraph/Drawable.h"
#include "Physics/Physics.h"

#include "magnumDebugToolsVisibility.h"

namespace Magnum { namespace DebugTools {

/** @todoc Remove `ifndef` when Doxygen is sane again */
#ifndef DOXYGEN_GENERATING_OUTPUT
template<UnsignedInt> class ShapeRenderer;
#endif

#ifndef DOXYGEN_GENERATING_OUTPUT
namespace Implementation {
    template<UnsignedInt> class AbstractShapeRenderer;

    template<UnsignedInt dimensions> void createDebugMesh(ShapeRenderer<dimensions>* renderer, Physics::AbstractShape<dimensions>* shape);
}
#endif

/**
@brief Shape renderer options

See ShapeRenderer documentation for more information.
*/
class ShapeRendererOptions {
    public:
        inline constexpr ShapeRendererOptions(): _color(1.0f), _pointSize(0.25f) {}

        /** @brief Color of rendered shape */
        inline constexpr Color4<> color() const { return _color; }

        /**
         * @brief Set color of rendered shape
         * @return Pointer to self (for method chaining)
         *
         * Default is 100% opaque white.
         */
        inline ShapeRendererOptions* setColor(const Color4<>& color) {
            _color = color;
            return this;
        }

        /** @brief Point size */
        inline constexpr Float pointSize() const { return _pointSize; }

        /**
         * @brief Set point size
         * @return Pointer to self (for method chaining)
         *
         * Size of rendered crosshairs, representing Physics::Point shapes.
         * Default is `0.25f`.
         */
        inline ShapeRendererOptions* setPointSize(Float size) {
            _pointSize = size;
            return this;
        }

    private:
        Color4<> _color;
        Float _pointSize;
};

/**
@brief Shape renderer

Visualizes collision shapes using wireframe primitives. See
@ref debug-tools-renderers for more information.

@section ShapeRenderer-usage Basic usage

Example code:
@code
// Create some options
DebugTools::ResourceManager::instance()->set("red", (new DebugTools::ShapeRendererOptions)
    ->setColor({1.0f, 0.0f, 0.0f}));

// Create debug renderer for given shape, use "red" options for it
Physics::ObjectShape2D* shape;
new DebugTools::ShapeRenderer2D(shape, "red", debugDrawables);
@endcode

@see ShapeRenderer2D, ShapeRenderer3D
*/
template<UnsignedInt dimensions> class MAGNUM_DEBUGTOOLS_EXPORT ShapeRenderer: public SceneGraph::Drawable<dimensions> {
    #ifndef DOXYGEN_GENERATING_OUTPUT
    friend void Implementation::createDebugMesh<>(ShapeRenderer<dimensions>*, Physics::AbstractShape<dimensions>*);
    #endif

    public:
        /**
         * @brief Constructor
         * @param shape     Object for which to create debug renderer
         * @param options   Options resource key. See
         *      @ref ShapeRenderer-usage "class documentation" for more
         *      information.
         * @param drawables Drawable group
         *
         * The renderer is automatically added to shape's object features,
         * @p shape must be available for the whole lifetime of the renderer.
         *
         * @attention Passed object must have assigned shape.
         */
        explicit ShapeRenderer(Physics::ObjectShape<dimensions>* shape, ResourceKey options = ResourceKey(), SceneGraph::DrawableGroup<dimensions>* drawables = nullptr);

        ~ShapeRenderer();

    protected:
        /** @todoc Remove Float when Doxygen properly treats this as override */
        void draw(const typename DimensionTraits<dimensions, Float>::MatrixType& transformationMatrix, SceneGraph::AbstractCamera<dimensions, Float>* camera) override;

    private:
        Resource<ShapeRendererOptions> options;
        std::vector<Implementation::AbstractShapeRenderer<dimensions>*> renderers;
};

/** @brief Two-dimensional shape renderer */
typedef ShapeRenderer<2> ShapeRenderer2D;

/** @brief Three-dimensional shape renderer */
typedef ShapeRenderer<3> ShapeRenderer3D;

}}

#endif
