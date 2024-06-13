Họ và tên: Trần Hùng Anh
MSSV: 22120016

Đồ án game 2048 Kỹ thuật lập trình

Video demo: https://drive.google.com/drive/folders/1V184gKfmY2EO9St-HoPOS8JRz_vWam92?usp=sharing

Cách build game: game chỉ hoạt động trên hệ điều hành Windows
    -B1: Tải và cài đặt MinGW để compile code
    -B2: vào thư mục 2048 của game có chứa file main.cpp, mở terminal đến thư mục
    -B3: chạy dòng lệnh sau:
        $cppFiles = Get-ChildItem -Recurse -Filter *.cpp | ForEach-Object { $_.FullName }
        g++ -o main $cppFiles
    -B4: build thành công file main.exe, chạy file main.exe để bắt đầu chơi


Gameplay:
Màn hình chính:
    Sử dụng mũi tên lên và mũi tên xuống để lựa chọn giữa các mục (New Game, Resume, Setting, Top 20), nhấn Enter để chọn.

Setting:
    -Nhấn phím mũi tên lên xuống để lựa chọn giữa "Enable Undo/Redo" và "Độ lớn của game"
    -Enable Undo/Redo: Nhấn Enter để đổi giữa cho phép và không cho phép Redo/Undo
    -Dùng phím mũi tên trái phải để thay đổi kích thước của game (nhỏ nhất là 4x4 và lớn nhất là 16x16);
    -Nhấn Esc để về màn hình chính

Resume:
    -Màn hình hiện ra 5 slot cho người chơi lựa chọn
    -Nếu slot chưa có thông tin, màn hình sẽ hiện "Empty", nếu người chơi lựa chọn phần này sẽ được đưa về màn hình chính.
    -Sử dụng mũi tên lên xuống để lựa chọn các slot khác nhau, Enter để chọn.

New Game:
    -Game sẽ yêu cầu người dùng nhập tên, không quá 10 ký tự
    -Sử dụng các nút mũi tên để chơi game, R để Redo, E để Undo (nếu đã Enable Undo/Redo).
    -Nhấn Esc để thoát khỏi trò chơi, người dùng sẽ được yêu cầu chọn Slot save game.
    -Khi đạt 1 ô 2048, game sẽ hiện thông báo win game, người chơi được phép chọn chơi tiếp hoặc thoát.