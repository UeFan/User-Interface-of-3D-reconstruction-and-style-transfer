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

#include "ui/custom_widget3_for_style_transfer.h"

#include "ui/main_window.h"

namespace colmap {

CustomWidget3::CustomWidget3(MainWindow* main_window)
    : OptionsWidget(main_window),
      main_window_(main_window),
      thread_control_widget_(new ThreadControlWidget(this)) {
  setWindowTitle("Style Transfer");
  AddOptionFilePath(&mesh_path, "Mesh path");
  AddSpacer();
  AddOptionFilePath(&target_image_path, "Target image path");
  AddSpacer();
  AddOptionDirPath(&output_path, "Output folder");
  AddSpacer();

  QGridLayout* name_layout;
  name_layout = new QGridLayout(this);
  name_layout->setVerticalSpacing(2);
  name_layout->setAlignment(Qt::AlignTop);
//  setLayout(grid_layout_);
  QLabel* output_name_label = new QLabel(tr("Output name"), this);
  QLineEdit *output_name = new QLineEdit(this);
  output_name->resize(120,20);
  name_layout->addWidget(output_name_label, 0, 0);
  name_layout->addWidget(output_name, 0, 1);
  grid_layout_->addLayout(name_layout, grid_layout_->rowCount()+1, 1);
//  QLabel* data_type_label = new QLabel(tr("Data type"), this);
//  data_type_label->setFont(font());
//  data_type_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//  grid_layout_->addWidget(data_type_label, grid_layout_->rowCount(), 0);

//  data_type_cb_ = new QComboBox(this);
//  data_type_cb_->addItem("Individual images");
//  data_type_cb_->addItem("Video frames");
//  data_type_cb_->addItem("Internet images");
//  grid_layout_->addWidget(data_type_cb_, grid_layout_->rowCount() - 1, 1);

//  QLabel* quality_label = new QLabel(tr("Quality"), this);
//  quality_label->setFont(font());
//  quality_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//  grid_layout_->addWidget(quality_label, grid_layout_->rowCount(), 0);

//  quality_cb_ = new QComboBox(this);
//  quality_cb_->addItem("Low");
//  quality_cb_->addItem("Medium");
//  quality_cb_->addItem("High");
//  quality_cb_->setCurrentIndex(2);
//  grid_layout_->addWidget(quality_cb_, grid_layout_->rowCount() - 1, 1);


//  AddOptionBool(, "Shared intrinsics");
//  AddOptionBool(, "Sparse model");
//  AddOptionBool( , "Dense model");
//  AddOptionBool(.use_gpu, "GPU");

  AddSpacer();

  QPushButton* run_button = new QPushButton(tr("Run"), this);
  grid_layout_->addWidget(run_button, grid_layout_->rowCount(), 0);
  connect(run_button, &QPushButton::released, this,
          &CustomWidget3::Run);

  QPushButton* browse_button = new QPushButton(tr("Browse"), this);
  grid_layout_->addWidget(browse_button, grid_layout_->rowCount()-2, 0);
  connect(browse_button, &QPushButton::released, this,
          &CustomWidget3::Browse);

  render_result_ = new QAction(this);
  connect(render_result_, &QAction::triggered, this,
          &CustomWidget3::RenderResult, Qt::QueuedConnection);
}

void CustomWidget3::Run() {

}
void CustomWidget3::Browse() {

    QMovie * gif_left = new QMovie("/Users/fanyue/Downloads/output/cat.gif");
    QLabel* label_left = new QLabel(this);
    label_left->setMovie(gif_left);
    label_left->setFixedSize(400,400);
    label_left->setScaledContents(true);
    grid_layout_->addWidget(label_left, grid_layout_->rowCount(),0);
    gif_left->start();

    QMovie * gif_right = new QMovie("/Users/fanyue/Downloads/output/cat_tree.gif");
    QLabel* label_right = new QLabel(this);
    label_right->setMovie(gif_right);
    label_right->setFixedSize(400,400);
    label_right->setScaledContents(true);
    grid_layout_->addWidget(label_right, grid_layout_->rowCount()-1,1);
    gif_right->start();

}

void CustomWidget3::RenderResult() {


}

}  // namespace colmap
