object Test extends App {
  
  //println (countChange(4, List(1,2), List())) // 3
  // println (countChange(50, List(1,2,5,10,20,50,100), List())) // 451
  println (countChange(100, List(1,2,5,10,20,50,100), List()))
  
  def countChange(money: Int, coins: List[Int], usedCoins: List[Int]): Int = 
    if (money == 0) { /*println(usedCoins);*/ 1}
    else if ((money < 0) || coins.isEmpty) 0
    else countChange (money - coins.head, coins, coins.head :: usedCoins) + countChange(money, coins.tail, usedCoins)

}
