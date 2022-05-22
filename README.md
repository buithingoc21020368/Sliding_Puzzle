# Sliding puzzle

## Hướng dẫn cài đặt:

- Bước 1: cài MinGW
- Bước 2: mở command port tại tệp muốn lưu code tải về
- Bước 3: clone code về máy bằng lệnh: git clone https://github.com/buithingoc21020368/Sliding_Puzzle
- Bước 4: vào code vừa tải bằng lệnh: "cd Sliding_Puzzle"
- Bước 5: biên dịch code bằng lệnh: "mingw32-make"
- Bước 6: chạy code bằng lệnh: "Sliding_Puzzle.exe"

## Mô tả chung về trò chơi:

- Đây là trò chơi xếp hình. Mỗi hình ảnh sẽ được chia thành nhiều mảnh nhỏ và bị xáo trộn đi. Nhiệm vụ của bạn là sắp xếp các mảnh ghép ấy về đúng vị trí để được một tấm hình hoàn chỉnh

## Mô tả các chức năng đã cài đặt:

- Các mức độ chơi: 3x3, 4x4, 5x5, ...
- Lựa chọn hình ảnh ngẫu nhiên : rand ảnh trong kho ảnh
- Chơi lại : nút SPACE

## Các kĩ thuật lập trình được sử dụng:

- Thuật toán random
- Thuật toán stack để hiển thị các render

## Kết luận, hướng phát triển, các điều tâm đắc:

- Thêm giới hạn về thời gian
- Có bảng điểm
- Thêm chế độ quay trở lại menu sau khi chơi xong
- Có các hình ảnh các loại
