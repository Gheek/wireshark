/* voip_calls_dialog.h
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef VOIP_CALLS_DIALOG_H
#define VOIP_CALLS_DIALOG_H

#include <config.h>

#include <glib.h>

#include "cfile.h"

#include "ui/voip_calls.h"

#include <ui/qt/models/voip_calls_info_model.h>
#include <ui/qt/models/cache_proxy_model.h>
#include "wireshark_dialog.h"

#include <QMenu>

class QAbstractButton;

class SequenceInfo;

namespace Ui {
class VoipCallsDialog;
}

class VoipCallsDialog : public WiresharkDialog
{
    Q_OBJECT

public:
    explicit VoipCallsDialog(QWidget &parent, CaptureFile &cf, bool all_flows = false);
    ~VoipCallsDialog();

public slots:
    void endRetapPackets();

signals:
    void updateFilter(QString filter, bool force = false);
    void captureFileChanged(capture_file *cf);
    void goToPacket(int packet_num);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

protected slots:
    void changeEvent(QEvent* event);

private:
    Ui::VoipCallsDialog *ui;
    VoipCallsInfoModel *call_infos_model_;
    CacheProxyModel *cache_model_;
    QSortFilterProxyModel *sorted_model_;

    QWidget &parent_;
    voip_calls_tapinfo_t tapinfo_;
    SequenceInfo *sequence_info_;
    QPushButton *prepare_button_;
    QPushButton *sequence_button_;
    QPushButton *player_button_;
    QPushButton *copy_button_;
    QMenu ctx_menu_;

    // Tap callbacks
//    static void tapReset(void *tapinfo_ptr);
    static gboolean tapPacket(void *tapinfo_ptr, packet_info *pinfo, epan_dissect_t *, const void *data);
    static void tapDraw(void *tapinfo_ptr);

    void updateCalls();
    void prepareFilter();
    void showSequence();
    void showPlayer();

    QList<QVariant> streamRowData(int row) const;

private slots:
    void captureFileClosing();
    void on_callTreeView_activated(const QModelIndex &index);
    void on_actionSelect_All_triggered();
    void on_actionCopyAsCsv_triggered();
    void on_actionCopyAsYaml_triggered();
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_buttonBox_helpRequested();
    void on_todCheckBox_stateChanged(int state);
    void updateWidgets();
};

#endif // VOIP_CALLS_DIALOG_H

/*
 * Editor modelines
 *
 * Local Variables:
 * c-basic-offset: 4
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * ex: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */
