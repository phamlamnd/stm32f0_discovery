Các bước thiết lập ngắt
1.Xác định ID ngắt cần sử dụng: EXTI0 -> ID5 Interrupt = 5 -> PA0
2.Cập nhật Handler interrupt tương ứng trong bảng software vector
3.Thiết lập cho phép ngắt mức ngoại vi
	->GPIO: Input
	->EXTI0
	->SYSCFG_SYSCFG_EXTICR1[3:0]
4.Thiết lập mức priority
5.Thiết lập ngắt NVIC
6.Bật ngắt toàn cục cpsie i
7.Khi ra khỏi ngắt cần xóa cờ ngắt trong NVIC và ngoại vi