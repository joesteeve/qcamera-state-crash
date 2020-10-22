#include <functional>
#include <iostream>

#include <QApplication>
#include <QCamera>
#include <QCameraInfo>
#include <QObject>
#include <QtGlobal>
#include <QTimer>

class Camera : public QObject
{
public:
  bool start(std::function<void()> done_cb)
  {
    m_done_cb = done_cb;

    auto camera_info = QCameraInfo::defaultCamera();
    if (camera_info.isNull()) {
      qInfo() << "No viable camera";
      return false;
    }

    m_camera = new QCamera(camera_info);
    connect(m_camera, &QCamera::stateChanged, this, &Camera::on_state_change);
    connect(
      m_camera, &QCamera::statusChanged, this, &Camera::on_status_change);
    qInfo() << "--- Loading ---";
    m_camera->load();
    return true;
  }

  void on_state_change(QCamera::State state)
  {
    qInfo() << "State change: " << state;

    if (state == QCamera::LoadedState) {}

    if (state == QCamera::UnloadedState) {
      //QTimer::singleShot(1, this, &Camera::destroy_camera);
      destroy_camera();
    }
  }

  void on_status_change(QCamera::Status status)
  {
    qInfo() << "Status change: " << status;

    if (status == QCamera::LoadedStatus) {
      qInfo() << "--- Unloading ---";
      m_camera->unload();
    }

    if (status == QCamera::UnloadedStatus) {}
  }

  void destroy_camera()
  {
    delete m_camera;
    m_done_cb();
  }

private:
  std::function<void()> m_done_cb;
  QCamera* m_camera = nullptr;
};

QApplication* g_app = nullptr;

void
on_done()
{
  g_app->quit();
}

int
main(int argc, char** argv)
{
  g_app = new QApplication(argc, argv);
  Camera camera;
  auto ret = camera.start(&on_done);
  if (ret == false) {
    return 1;
  }
  g_app->exec();
  return 0;
}
