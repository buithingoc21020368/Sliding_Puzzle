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
- Âm thanh khi di chuyển chuột và khi click vào một mảnh hình ảnh bất ký
- Đếm số lần click chuột
- Video demo: https://drive.google.com/file/d/16uk853l6dbYS-8sD06wxu8jftEmJ5KKr/view?usp=sharing

## Các kĩ thuật lập trình được sử dụng:

- Thuật toán random
- Thuật toán stack để hiển thị các render

## Kết luận, hướng phát triển, các điều tâm đắc:

Game đã tương đối hoàn chỉnh: có đồ hoạ, âm thanh, menu, thông báo, tính số lượt di chuyển

Hướng cải tiến:
- Thêm giới hạn về thời gian, bảng điểm, nút bật tắt âm thanh, chế độ quay trở lại menu sau khi chơi xong
- Đa dạng các hình ảnh hơn
- Cải tiến hàm xáo trộn hình ảnh để cùng một hình và một mức độ chơi có thể chơi được nhiều lần mà không bị trùng lặp, đảm bảo thứ tự các hình ảnh đã xáo trộn có thể đưa về hình gốc được 

Điều tâm đắc: 
- Học được cách cài đặt thư viện, setup môi trường
- Cải tiến các chức năng của game
- Tìm hiểu và xác định được một n-puzzle có thể chuyển về trạng thái đích với số lần di chuyển bất kỳ hay không (điều này em mới chỉ hiểu nhưng chưa áp dụng được vào game của mình, sẽ dùng để cải tiến game)
