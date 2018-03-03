wget https://github.com/graph500/graph500/archive/graph500-2.1.4.tar.gz

tar -xvf ./graph500-2.1.4.tar.gz

mv graph500-graph500-2.1.4/ graph500-2.1.4/

cd ./graph500-2.1.4/

cp ./make-incs/make.inc-gcc ./make.inc

edit your make.inc and remove -DUSE_MMAP_LARGE -DUSE_MMAP_LARGE_EXT from there 

make

./seq-csr/seq-csr -s 22 -e 16

衡量指标：harmonic_mean_TEPS

---
参考资料：
https://github.com/graph500/graph500/tree/graph500-2.1.4

https://graph500.org/?page_id=12

https://stackoverflow.com/questions/41994040/how-to-compile-dan-run-graph500-benchmark



