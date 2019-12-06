// COLMAP - Structure-from-Motion and Multi-View Stereo.
// Copyright (C) 2017  Johannes L. Schoenberger <jsch at inf.ethz.ch>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef COLMAP_SRC_UI_CUSTON_WIDGET3_FOR_STYLE_TRANSFER_H_
#define COLMAP_SRC_UI_CUSTON_WIDGET3_FOR_STYLE_TRANSFER_H_


#include "ui/options_widget.h"
#include "ui/thread_control_widget.h"

namespace colmap {
class MainWindow;

class CustomWidget3 : public OptionsWidget {
 public:
  CustomWidget3(MainWindow* main_window);

  void Run();
  void Browse();

 private:
  void RenderResult();
  std::string mesh_path;
  std::string target_image_path;
  std::string output_path;

  MainWindow* main_window_;
  ThreadControlWidget* thread_control_widget_;
  QComboBox* data_type_cb_;
  QComboBox* quality_cb_;
  QAction* render_result_;

};


    
    
}  // namespace colmap

#endif  // COLMAP_SRC_UI_CUSTON_WIDGET3_FOR_STYLE_TRANSFER_H_
