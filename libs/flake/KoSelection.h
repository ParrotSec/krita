/* This file is part of the KDE project

   Copyright (C) 2006 Boudewijn Rempt <boud@valdyas.org>
   Copyright (C) 2006 Thorsten Zachmann <zachmann@kde.org>
   Copyright (C) 2007,2009 Thomas Zander <zander@kde.org>
   Copyright (C) 2006,2007 Jan Hambrecht <jaham@gmx.net>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#ifndef KOSELECTION_H
#define KOSELECTION_H

#include <QObject>

#include "KoShape.h"
#include "KoFlake.h"

#include "kritaflake_export.h"

class KoViewConverter;
class KoShapeLayer;
class KoSelectionPrivate;

/**
 * A selection is a shape that contains a number of references
 * to shapes. That means that a selection can be manipulated in
 * the same way as a single shape.
 *
 * Note that a single shape can be selected in one view, and not in
 * another, and that in a single view, more than one selection can be
 * present. So selections should not be seen as singletons, or as
 * something completely transient.
 *
 * A selection, however, should not be selectable. We need to think
 * a little about the interaction here.
 */
class KRITAFLAKE_EXPORT KoSelection : public QObject, public KoShape
{
    Q_OBJECT

public:

    KoSelection();
    virtual ~KoSelection();

    virtual void paint(QPainter &painter, const KoViewConverter &converter, KoShapePaintingContext &paintcontext);

    /**
     * Adds a shape to the selection.
     *
     * If the shape is a KoShapeGroup all of its child shapes are automatically added
     * to the selection.
     * If the shape has no parent or is not a KoShapeGroup, only the given shape is
     * added to the selection.
     * If the given shape is a child of a KoShapeGroup and recursive selection is enabled
     * the all parents and their child shapes up to the toplevel KoShapeGroup are added to
     * the selection.
     *
     * @param shape the shape to add to the selection
     * @param recursive enables recursively selecting shapes of parent groups
     */
    void select(KoShape *shape, bool recursive = true);

    /**
     * Removes a selected shape.
     *
     * If the shape is a KoShapeGroup all of its child shapes are automatically removed
     * from the selection.
     * If the shape has no parent or is not a KoShapeGroup, only the given shape is
     * removed from the selection.
     * If the given shape is a child of a KoShapeGroup and recursive selection is enabled
     * the all parents and their child shape up to the toplevel KoShapeGroup are removed
     * from the selection.
     *
     * @param shape the shape to remove from the selection
     * @param recursive enables recursively deselecting shapes of parent groups
     */
    void deselect(KoShape *shape, bool recursive = true);

    /// clear the selections list
    void deselectAll();

    /**
     * Return the list of selected shapes
     * @return the list of selected shapes
     * @param strip if StrippedSelection, the returned list will not include any children
     *    of a container shape if the container-parent is itself also in the set.
     */
    const QList<KoShape*> selectedShapes(KoFlake::SelectionType strip = KoFlake::FullSelection) const;

    /**
     * Return the first selected shape, or 0 if there is nothing selected.
     * @param strip if StrippedSelection, the returned list will not include any children
     *    of a grouped shape if the group-parent is itself also in the set.
     */
    KoShape *firstSelectedShape(KoFlake::SelectionType strip = KoFlake::FullSelection) const;

    /// return true if the shape is selected
    bool isSelected(const KoShape *shape) const;

    /// return the selection count, i.e. the number of all selected shapes
    int count() const;

    virtual bool hitTest(const QPointF &position) const;

    virtual QRectF boundingRect() const;

    /**
     * Sets the currently active layer.
     * @param layer the new active layer
     */
    void setActiveLayer(KoShapeLayer *layer);

    /**
     * Returns a currently active layer.
     *
     * @return the currently active layer, or zero if there is none
     */
    KoShapeLayer *activeLayer() const;

    /// Updates the size and position of the selection
    void updateSizeAndPosition();

Q_SIGNALS:
    /// emitted when the selection is changed
    void selectionChanged();

    /// emitted when the current layer is changed
    void currentLayerChanged(const KoShapeLayer *layer);

private:
    virtual void saveOdf(KoShapeSavingContext &) const;
    virtual bool loadOdf(const KoXmlElement &, KoShapeLoadingContext &);

    Q_PRIVATE_SLOT(d_func(), void selectionChangedEvent())
    Q_DECLARE_PRIVATE_D(KoShape::d_ptr, KoSelection)
};

#endif
