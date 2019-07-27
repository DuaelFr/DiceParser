/***************************************************************************
 * Copyright (C) 2014 by Renaud Guezennec                                   *
 * http://www.rolisteam.org/contact                      *
 *                                                                          *
 *  This file is part of DiceParser                                         *
 *                                                                          *
 * DiceParser is free software; you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by     *
 * the Free Software Foundation; either version 2 of the License, or        *
 * (at your option) any later version.                                      *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             *
 * GNU General Public License for more details.                             *
 *                                                                          *
 * You should have received a copy of the GNU General Public License        *
 * along with this program; if not, write to the                            *
 * Free Software Foundation, Inc.,                                          *
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.                 *
 ***************************************************************************/
#ifndef PARSINGTOOLBOX_H
#define PARSINGTOOLBOX_H

#include <QMap>

#include "booleancondition.h"
#include "compositevalidator.h"
#include "node/dicerollernode.h"
#include "node/executionnode.h"
#include "node/ifnode.h"
#include "node/paintnode.h"
#include "node/scalaroperatornode.h"
#include "operationcondition.h"
#include "range.h"

class SubtituteInfo
{
public:
    SubtituteInfo();

    bool isValid() const;

    int length() const;
    void setLength(int length);

    int resultIndex() const;
    void setResultIndex(int valueIndex);

    int position() const;
    void setPosition(int position);

    int digitNumber() const;
    void setDigitNumber(int digitNumber);

private:
    int m_length= 2;
    int m_digitNumber= 0;
    int m_resultIndex= -1;
    int m_position= -1;
};

/**
 * @brief The ParsingToolBox is gathering many useful methods for dice parsing.
 * Its goal is to make the diceparser a bit lighter.
 */
class ParsingToolBox
{
public:
    enum LIST_OPERATOR
    {
        NONE,
        UNIQUE
    };

    /**
     * @brief ParsingToolBox
     */
    ParsingToolBox();
    /**
     * @brief ParsingToolBox
     * @param data
     */
    ParsingToolBox(const ParsingToolBox& data);
    /**
     * @brief ~ParsingToolBox
     */
    virtual ~ParsingToolBox();
    /**
     * @brief addSort
     * @param e
     * @param b
     * @return
     */
    ExecutionNode* addSort(ExecutionNode* e, bool b);
    /**
     * @brief readAscending
     * @param str
     * @return
     */
    static bool readAscending(QString& str);
    /**
     * @brief readLogicOperator
     * @param str
     * @param op
     * @return
     */
    bool readLogicOperator(QString& str, BooleanCondition::LogicOperator& op);
    /**
     * @brief readValidator
     * @param str
     * @return
     */
    Validator* readValidator(QString& str, bool hasSquare=false);
    /**
     * @brief readCompositeValidator
     * @param str
     * @return
     */
    Validator* readCompositeValidator(QString& str);

    /**
     * @brief readNumber read number in the given str and remove from the string the read character.
     * @param str the command line
     * @param myNumber reference to the found number
     * @return true, succeed to read number, false otherwise.
     */
    static bool readNumber(QString& str, qint64& myNumber);

    /**
     * @brief readString
     * @param str
     * @param strResult
     * @return
     */
    static bool readString(QString& str, QString& strresult);
    /**
     * @brief readVariable
     * @param str
     * @param myNumber
     * @return
     */
    static bool readVariable(QString& str, qint64& myNumber, QString& reasonFail);
    /**
     * @brief readOpenParentheses
     * @param str
     * @return
     */
    static bool readOpenParentheses(QString& str);
    /**
     * @brief readCloseParentheses
     * @param str
     * @return
     */
    static bool readCloseParentheses(QString& str);

    /**
     * @brief readNumber read number in the given str and remove from the string the read character.
     * @param str the command line
     * @param myNumber reference to the found number
     * @return true, succeed to read number, false otherwise.
     */
    static bool readDynamicVariable(QString& str, qint64& index);

    /**
     * @brief readList
     * @param str
     * @param list
     * @return
     */
    bool readList(QString& str, QStringList& list, QList<Range>& ranges);
    /**
     * @brief isValidValidator
     * @param previous
     * @param val
     * @return
     */
    Dice::CONDITION_STATE isValidValidator(ExecutionNode* previous, Validator* val);
    /**
     * @brief getDiceRollerNode
     * @param previous
     * @return
     */
    DiceRollerNode* getDiceRollerNode(ExecutionNode* previous);

    /**
     * @brief readDiceRange
     * @param str
     * @param start
     * @param end
     * @return
     */
    bool readDiceRange(QString& str, qint64& start, qint64& end);
    /**
     * @brief readListOperator
     * @param str
     * @return
     */
    static LIST_OPERATOR readListOperator(QString& str);

    void readProbability(QStringList& str, QList<Range>& ranges);

    bool readLogicOperation(QString& str, CompositeValidator::LogicOperation& op);

    bool readDiceLogicOperator(QString& str, OperationCondition::ConditionOperator& op);

    bool readArithmeticOperator(QString& str, Die::ArithmeticOperator& op);

    static bool readPainterParameter(PainterNode* painter, QString& str);

    static QHash<QString, QString> getVariableHash();
    static void setVariableHash(const QHash<QString, QString>& variableHash);
    /**
     * @brief readConditionType
     * @param str
     * @return
     */
    static IfNode::ConditionType readConditionType(QString& str);

    bool readComment(QString& str, QString&, QString&);
    static ExecutionNode* getLatestNode(ExecutionNode* node);

    static std::vector<ExecutionNode*>* getStartNodes();
    static void setStartNodes(std::vector<ExecutionNode*>* startNodes);

    static bool readOperand(QString& str, ExecutionNode*& node);
    static int findClosingCharacterIndexOf(QChar open, QChar closing, const QString& str, int offset);

    static QString replaceVariableToValue(const QString& source, QStringList values);

    static SubtituteInfo readVariableFromString(const QString& source, int& start);

    static void readSubtitutionParameters(SubtituteInfo& info, QString& rest);

    static bool readComma(QString& str);

private:
    QMap<QString, BooleanCondition::LogicOperator>* m_logicOp;
    QMap<QString, CompositeValidator::LogicOperation>* m_logicOperation;
    QMap<QString, OperationCondition::ConditionOperator>* m_conditionOperation;
    QHash<QString, Die::ArithmeticOperator>* m_arithmeticOperation;

    static QHash<QString, QString> m_variableHash;
    static std::vector<ExecutionNode*>* m_startNodes;
};

#endif // PARSINGTOOLBOX_H
