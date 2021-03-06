/* @@@LICENSE
*
*      Copyright (c) 2011-2013 LG Electronics, Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */




#include "demogoggles3.h"
#include "pixmapobject.h"
#include "dimensionsglobal.h"
#include <QString>
#include <QRectF>
#include <QPainter>
#include <QDebug>
#include <QGLShaderProgram>

#define shaderprogfilepath QString("/var/luna/preferences/launcher3/blurshader2.frag")

DemoGoggles3::DemoGoggles3(const QRectF& geometry,PixmapObject * p_backgroundPmo,const QRectF& viewRect)
: ThingPaintable(geometry)
, m_qp_backgroundPmo(p_backgroundPmo)
, m_sceneBgViewrect(viewRect)
{
	setGraphicsEffect(&m_effect);
	m_effect.setEnabled(false);
	if (!m_qp_backgroundPmo)
	{
		setFlag(ItemHasNoContents,true);
	}

}

//virtual
DemoGoggles3::~DemoGoggles3()
{
	delete m_qp_backgroundPmo;
}

//virtual
void DemoGoggles3::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
	//map myself into the scene
	QRectF sceneRect = mapRectToScene(boundingRect());
	QRectF sourceRect = sceneRect.intersected(m_sceneBgViewrect).translated(-m_sceneBgViewrect.topLeft());
	m_qp_backgroundPmo->paint(painter,boundingRect().toRect(),sourceRect.toRect());
}

//virtual
void DemoGoggles3::paintOffscreen(QPainter *painter)
{
}

//virtual
void DemoGoggles3::updateBackground(PixmapObject * p_newBgPmo,const QRectF& viewRect)
{
	delete m_qp_backgroundPmo;
	m_qp_backgroundPmo = p_newBgPmo;
	m_sceneBgViewrect = viewRect;
	if (!m_qp_backgroundPmo)
	{
		setFlag(ItemHasNoContents,true);
	}
	else
	{
		setFlag(ItemHasNoContents,false);
	}

}

//virtual
void DemoGoggles3::activate()
{
	m_effect.setEnabled(true);
}

//virtual
void DemoGoggles3::deactivate()
{
	m_effect.setEnabled(false);
}
