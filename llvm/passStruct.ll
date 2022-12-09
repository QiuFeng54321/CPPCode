; ModuleID = 'passStruct.cpp'
source_filename = "passStruct.cpp"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%class.S = type { i32, i32, i32, i8, [4 x [5 x i32]] }

@arr = global [3 x [3 x i64]] [[3 x i64] [i64 1, i64 2, i64 3], [3 x i64] [i64 4, i64 5, i64 6], [3 x i64] [i64 7, i64 8, i64 9]], align 16

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define noundef zeroext i1 @_Z4test1S(%class.S* noundef byval(%class.S) align 8 %0) #0 {
  %2 = getelementptr inbounds %class.S, %class.S* %0, i32 0, i32 1
  store i32 3, i32* %2, align 4
  %3 = getelementptr inbounds %class.S, %class.S* %0, i32 0, i32 0
  %4 = load i32, i32* %3, align 8
  %5 = icmp ne i32 %4, 0
  ret i1 %5
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define noundef zeroext i1 @_Z5test2P1S(%class.S* noundef %0) #0 {
  %2 = alloca %class.S*, align 8
  store %class.S* %0, %class.S** %2, align 8
  %3 = load %class.S*, %class.S** %2, align 8
  %4 = getelementptr inbounds %class.S, %class.S* %3, i32 0, i32 1
  store i32 3, i32* %4, align 4
  %5 = load %class.S*, %class.S** %2, align 8
  %6 = getelementptr inbounds %class.S, %class.S* %5, i32 0, i32 0
  %7 = load i32, i32* %6, align 4
  %8 = icmp ne i32 %7, 0
  ret i1 %8
}

; Function Attrs: mustprogress noinline nounwind optnone ssp uwtable
define noundef i32 @_Z1pv() #0 {
  %1 = alloca i64, align 8
  %2 = load i64, i64* getelementptr inbounds ([3 x [3 x i64]], [3 x [3 x i64]]* @arr, i64 0, i64 1, i64 2), align 8
  store i64 %2, i64* %1, align 8
  ret i32 0
}

; Function Attrs: mustprogress noinline norecurse nounwind optnone ssp uwtable
define noundef i32 @main() #1 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call noundef i32 @_Z1pv()
  ret i32 0
}

attributes #0 = { mustprogress noinline nounwind optnone ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse nounwind optnone ssp uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 1}
!3 = !{i32 7, !"frame-pointer", i32 2}
!4 = !{!"Homebrew clang version 14.0.6"}
