/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the tools applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QMLVISITOR_H
#define QMLVISITOR_H

#include <qstring.h>
#include "qqmljsastvisitor_p.h"
#include "node.h"
#include "tree.h"

QT_BEGIN_NAMESPACE

struct QmlPropArgs
{
    QString type_;
    QString module_;
    QString component_;
    QString name_;

    void clear() {
        type_.clear();
        module_.clear();
        component_.clear();
        name_.clear();
    }
};

class QmlDocVisitor : public QQmlJS::AST::Visitor
{
public:
    QmlDocVisitor(const QString &filePath,
                  const QString &code,
                  QQmlJS::Engine *engine,
                  QSet<QString> &commands,
                  QSet<QString> &topics);
    virtual ~QmlDocVisitor();

    bool visit(QQmlJS::AST::UiImportList *imports);
    void endVisit(QQmlJS::AST::UiImportList *definition);

    bool visit(QQmlJS::AST::UiObjectDefinition *definition);
    void endVisit(QQmlJS::AST::UiObjectDefinition *definition);

    bool visit(QQmlJS::AST::UiPublicMember *member);
    void endVisit(QQmlJS::AST::UiPublicMember *definition);

    bool visit(QQmlJS::AST::IdentifierPropertyName *idproperty);

    bool visit(QQmlJS::AST::FunctionDeclaration *);
    void endVisit(QQmlJS::AST::FunctionDeclaration *);

    bool visit(QQmlJS::AST::UiScriptBinding *);
    void endVisit(QQmlJS::AST::UiScriptBinding *);

    bool visit(QQmlJS::AST::UiQualifiedId *);
    void endVisit(QQmlJS::AST::UiQualifiedId *);

private:
    QQmlJS::AST::SourceLocation precedingComment(quint32 offset) const;
    bool applyDocumentation(QQmlJS::AST::SourceLocation location, Node *node);
    void applyMetacommands(QQmlJS::AST::SourceLocation location, Node* node, Doc& doc);
    bool splitQmlPropertyArg(const Doc& doc,
                             const QString& arg,
                             QmlPropArgs& qpa);

    QQmlJS::Engine *engine;
    quint32 lastEndOffset;
    quint32 nestingLevel;
    QString filePath;
    QString name;
    QString document;
    QList<QPair<QString, QString> > importList;
    QSet<QString> commands;
    QSet<QString> topics;
    QSet<quint32> usedComments;
    Tree *tree;
    InnerNode *current;
};

QT_END_NAMESPACE

#endif
