#include "InitUpdateButton.hpp"

#include "ab/FlatButton.hpp"
#include "widgets/dialogs/UpdateDialog.hpp"

namespace chatterino
{
    void initUpdateButton(
        ab::FlatButton& button, pajlada::Signals::SignalHolder& signalHolder)
    {
        button.hide();

        // show update prompt when clicking the button
        QObject::connect(&button, &ab::FlatButton::leftClicked, [&button] {
            auto dialog = new UpdateDialog();
            dialog->setActionOnFocusLoss(ab::BaseWindow::Delete);
            dialog->move(button.mapToGlobal(
                QPoint(int(-100 * button.scale()), button.height())));
            dialog->show();
            dialog->raise();

            dialog->buttonClicked.connect([&button](auto buttonType) {
                switch (buttonType)
                {
                    case UpdateDialog::Dismiss:
                    {
                        button.hide();
                    }
                    break;
                    case UpdateDialog::Install:
                    {
                        Updates::getInstance().installUpdates();
                    }
                    break;
                }
            });

            //        handle.reset(dialog);
            //        dialog->closing.connect([&handle] { handle.release(); });
        });

        // update image when state changes
        auto updateChange = [&button](auto) {
            button.setVisible(Updates::getInstance().shouldShowUpdateButton());

            // TODO: use resources class
            auto imageUrl = Updates::getInstance().isError()
                                ? ":/images/download_update_error.png"
                                : ":/images/download_update.png";
            button.setPixmap(QPixmap(imageUrl));
        };

        updateChange(Updates::getInstance().getStatus());

        signalHolder.managedConnect(Updates::getInstance().statusUpdated,
            [updateChange](auto status) { updateChange(status); });
    }
}  // namespace chatterino
