/* This file is part of the KDE project
 * Copyright (C) 2012 Arjen Hiemstra <ahiemstra@heimr.nl>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "kis_show_palette_action.h"

#include <QCursor>

#include <klocalizedstring.h>

#include <kis_favorite_resource_manager.h>
#include <kis_canvas2.h>

#include "kis_input_manager.h"

KisShowPaletteAction::KisShowPaletteAction()
    : KisAbstractInputAction("Show Popup Palette")
{
    setName(i18n("Show Popup Palette"));
    setDescription(i18n("The <i>Show Popup Palette</i> displays the popup palette."));
}

KisShowPaletteAction::~KisShowPaletteAction()
{

}

int KisShowPaletteAction::priority() const
{
    return 1;
}

void KisShowPaletteAction::begin(int, QEvent *event)
{
    QPoint pos = eventPos(event);
    if (pos.isNull()) {
        pos = inputManager()->canvas()->canvasWidget()->mapFromGlobal(QCursor::pos());
    }

    inputManager()->canvas()->slotShowPopupPalette(pos);
}
