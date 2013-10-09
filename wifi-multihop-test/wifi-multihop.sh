#scratch下のwifi-multihop-test.ccを並列計算するためのプログラム
#出力ファイルのために、ns-3.17下にsim_outディレクトリを作成しておく
 
for lambda in `seq 1.0 1.0 2.0`
do
    for i in `seq 1 4` #統計回数
    do
  ./waf --run "scratch/wifi-multihop-test --lambda=${lambda} --sim_count=${i}" &
    done
    wait
done
 
mv sim_out_* ./sim_out
