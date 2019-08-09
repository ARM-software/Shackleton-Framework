; ModuleID = 'main.cpp'
source_filename = "main.cpp"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.timeval = type { i64, i64 }
%struct.timezone = type { i32, i32 }

@.str = private unnamed_addr constant [129 x i8] c"clang++ -S -emit-llvm test.cpp && clang++ -S -emit-llvm math.cpp && llvm-link test.ll math.ll -S -o my_test.ll && opt my_test.ll\00", align 1
@.str.1 = private unnamed_addr constant [37 x i8] c"llvm-as my_test.ll && lli my_test.bc\00", align 1
@.str.2 = private unnamed_addr constant [54 x i8] c"The average time taken without any optimization: %f\0A\0A\00", align 1

; Function Attrs: noinline norecurse optnone uwtable
define i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  %7 = alloca [200 x i8], align 16
  %8 = alloca [50 x i8], align 16
  %9 = alloca %struct.timeval, align 8
  %10 = alloca %struct.timeval, align 8
  %11 = alloca double, align 8
  %12 = alloca double, align 8
  %13 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  store i32 20, i32* %6, align 4
  %14 = getelementptr inbounds [200 x i8], [200 x i8]* %7, i32 0, i32 0
  %15 = call i8* @strcpy(i8* %14, i8* getelementptr inbounds ([129 x i8], [129 x i8]* @.str, i32 0, i32 0)) #3
  %16 = getelementptr inbounds [200 x i8], [200 x i8]* %7, i32 0, i32 0
  %17 = call i32 @system(i8* %16)
  %18 = getelementptr inbounds [50 x i8], [50 x i8]* %8, i32 0, i32 0
  %19 = call i8* @strcpy(i8* %18, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.1, i32 0, i32 0)) #3
  store double 0.000000e+00, double* %11, align 8
  store double 0.000000e+00, double* %12, align 8
  store i32 0, i32* %13, align 4
  br label %20

; <label>:20:                                     ; preds = %48, %2
  %21 = load i32, i32* %13, align 4
  %22 = load i32, i32* %6, align 4
  %23 = icmp ult i32 %21, %22
  br i1 %23, label %24, label %51

; <label>:24:                                     ; preds = %20
  %25 = call i32 @gettimeofday(%struct.timeval* %9, %struct.timezone* null) #3
  %26 = getelementptr inbounds [50 x i8], [50 x i8]* %8, i32 0, i32 0
  %27 = call i32 @system(i8* %26)
  %28 = call i32 @gettimeofday(%struct.timeval* %10, %struct.timezone* null) #3
  %29 = getelementptr inbounds %struct.timeval, %struct.timeval* %10, i32 0, i32 0
  %30 = load i64, i64* %29, align 8
  %31 = getelementptr inbounds %struct.timeval, %struct.timeval* %9, i32 0, i32 0
  %32 = load i64, i64* %31, align 8
  %33 = sub nsw i64 %30, %32
  %34 = sitofp i64 %33 to double
  %35 = fmul double %34, 1.000000e+06
  store double %35, double* %12, align 8
  %36 = load double, double* %12, align 8
  %37 = getelementptr inbounds %struct.timeval, %struct.timeval* %10, i32 0, i32 1
  %38 = load i64, i64* %37, align 8
  %39 = getelementptr inbounds %struct.timeval, %struct.timeval* %9, i32 0, i32 1
  %40 = load i64, i64* %39, align 8
  %41 = sub nsw i64 %38, %40
  %42 = sitofp i64 %41 to double
  %43 = fadd double %36, %42
  %44 = fmul double %43, 0x3EB0C6F7A0B5ED8D
  store double %44, double* %12, align 8
  %45 = load double, double* %11, align 8
  %46 = load double, double* %12, align 8
  %47 = fadd double %45, %46
  store double %47, double* %11, align 8
  br label %48

; <label>:48:                                     ; preds = %24
  %49 = load i32, i32* %13, align 4
  %50 = add i32 %49, 1
  store i32 %50, i32* %13, align 4
  br label %20

; <label>:51:                                     ; preds = %20
  %52 = load double, double* %11, align 8
  %53 = load i32, i32* %6, align 4
  %54 = uitofp i32 %53 to double
  %55 = fdiv double %52, %54
  store double %55, double* %12, align 8
  %56 = load double, double* %12, align 8
  %57 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([54 x i8], [54 x i8]* @.str.2, i32 0, i32 0), double %56)
  %58 = load i32, i32* %3, align 4
  ret i32 %58
}

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #1

declare i32 @system(i8*) #2

; Function Attrs: nounwind
declare i32 @gettimeofday(%struct.timeval*, %struct.timezone*) #1

declare i32 @printf(i8*, ...) #2

attributes #0 = { noinline norecurse optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 5.0.0 (tags/RELEASE_500/final 365552) (llvm/tags/RELEASE_500/final 365550)"}
